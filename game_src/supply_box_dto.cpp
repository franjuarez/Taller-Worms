#include "supply_box_dto.h"


SupplyBoxDTO::SupplyBoxDTO(int id, int content, Position pos) : id(id), content(content), pos(pos) {}


float SupplyBoxDTO::getX() {
    return pos.getX();
}

float SupplyBoxDTO::getY() {
    return pos.getY();
}

int SupplyBoxDTO::getContent() {
    return content;
}

int SupplyBoxDTO::getID() {
    return id;
}

SupplyBoxDTO::~SupplyBoxDTO() {}