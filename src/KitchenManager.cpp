#include "KitchenManager.hpp"
#include "PipeIPC.hpp"
#include "Message.hpp"

#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <sys/wait.h>


KitchenManager::KitchenManager(int cooksPerKitchen, double multiplier, int restockTime)
  : _cooksPerKitchen(cooksPerKitchen),
    _multiplier(multiplier),
    _restockTime(restockTime),
    _nextKitchenId(1)
{
  createKitchen();
}

void KitchenManager::createKitchen() {
  int id = _nextKitchenId++;

  _kitchens.push_back(
    std::make_unique<Kitchen>(
        id,
        _cooksPerKitchen,
        _multiplier,
        _restockTime
    )
  );
  std::cout << "Kitchen " << id << " created" << std::endl;
}

void KitchenManager::forkedKitchenPrototype(const Pizza& pizza)
{
  int pipeFd[2];

  if (pipe(pipeFd) == -1)
    throw std::runtime_error("pipe failed");

  pid_t pid = fork();

  if (pid == -1)
    throw std::runtime_error("fork failed");

  if (pid == 0) {
    PipeIPC ipc(pipeFd[0], -1);

    close(pipeFd[1]);

    try {
      std::string rawMessage = ipc.receive();
      Message message = Message::unpack(rawMessage);

      if (message.getType() == MessageType::NewPizza && message.hasPizza()) {
        Pizza receivedPizza = message.getPizza();

        std::cout << "Forked kitchen received "
                  << receivedPizza.typeToString()
                  << " "
                  << receivedPizza.sizeToString()
                  << std::endl;
      }
    } catch (const std::exception& error) {
      std::cerr << "Forked kitchen error: "
                << error.what()
                << std::endl;
    }
    std::exit(0);
  }

  PipeIPC ipc(-1, pipeFd[1]);

  close(pipeFd[0]);

  Message message(MessageType::NewPizza, pizza);

  std::cout << "Reception sending to forked kitchen: "
            << message.pack()
            << std::endl;

  ipc.send(message.pack());

  waitpid(pid, nullptr, 0);
}



Kitchen& KitchenManager::getBestKitchen() {
  Kitchen* bestKitchen = nullptr;

  for (const auto& kitchen : _kitchens) {
    if (!kitchen->canAcceptPizza())
      continue;

    if (bestKitchen == nullptr || kitchen->getLoad() < bestKitchen->getLoad())
      bestKitchen = kitchen.get();
  }

  if (bestKitchen == nullptr) {
    createKitchen();
    return *_kitchens.back();
  }

  return *bestKitchen;
}

void KitchenManager::assignPizza(const Pizza& pizza) {
  Kitchen& kitchen = getBestKitchen();

  kitchen.addPizza(pizza);
}

void KitchenManager::displayStatus() const {
  for (const auto& kitchen : _kitchens)
    kitchen->displayStatus();
}
