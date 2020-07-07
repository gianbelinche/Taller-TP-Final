#include "../headers/Merchant.h"

#include "../headers/MasterFactory.h"

Merchant::Merchant(int id, int x, int y, ServerEventListener& eventListener,
                   MasterFactory& factory)
    : NPC(id, x, y, eventListener, factory) {
  itemsAvailable = {factory.createItem(ESPADA_TYPE),
                    factory.createItem(HACHA_TYPE),
                    factory.createItem(MARTILLO_TYPE),
                    factory.createItem(ARCOSIMPLE_TYPE),
                    factory.createItem(ARCOCOMPUESTO_TYPE),
                    factory.createItem(ARMADURAPLACAS_TYPE),
                    factory.createItem(ARMADURACUERO_TYPE),
                    factory.createItem(TUNICAAZUL_TYPE),
                    factory.createItem(CAPUCHA_TYPE),
                    factory.createItem(CASCOHIERRO_TYPE),
                    factory.createItem(ESCUDOTORTUGA_TYPE),
                    factory.createItem(ESCUDOHIERRO_TYPE)};
  npcType = MERCHANT_TYPE;
}

Merchant::~Merchant() {
  for (auto& item: itemsAvailable) {
    delete item;
  }
}
