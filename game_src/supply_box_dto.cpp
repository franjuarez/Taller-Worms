#include "supply_box_dto.h"


SupplyBoxDTO::SupplyBoxDTO(int id, int content, int falling, Position pos) : id(id), content(content), falling(falling), pos(pos) {}


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

int SupplyBoxDTO::isFalling() {
    return falling;
}

SupplyBoxDTO::~SupplyBoxDTO() {}