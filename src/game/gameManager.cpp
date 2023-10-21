#include "gameManager.hpp"
#include "engineStarter.hpp"

void onInit(const Event*) {
  printf("TEST INIT \n");
}

void onUpdate(const Event*) {
  printf("TEST UPDATE \n");
}

void onRender(const Event*) {
  printf("TEST RENDER \n");
}

void onRenderStop(const Event*) {
  printf("TEST RENDER STOP \n");
}

void onClose(const Event*) {
  printf("TEST CLOSE \n");
}

int GameManager::start() {
  CallbackFunctionPtr onInitPtr = std::make_shared<CallbackFunction>(onInit);
  CallbackFunctionPtr onUpdatePtr =
      std::make_shared<CallbackFunction>(onUpdate);
  CallbackFunctionPtr onRenderPtr =
      std::make_shared<CallbackFunction>(onRender);
  CallbackFunctionPtr onRenderStopPtr =
      std::make_shared<CallbackFunction>(onRenderStop);
  CallbackFunctionPtr onClosePtr = std::make_shared<CallbackFunction>(onClose);

  // TODO: batch subscribe to event manager
  engine.eventManager.subscribe(EventType::INIT, onInitPtr);
  engine.eventManager.subscribe(EventType::UPDATE, onUpdatePtr);
  engine.eventManager.subscribe(EventType::RENDER, onRenderPtr);
  engine.eventManager.subscribe(EventType::RENDER_STOP, onRenderStopPtr);
  engine.eventManager.subscribe(EventType::CLOSE, onClosePtr);

  return engine.start();
}
