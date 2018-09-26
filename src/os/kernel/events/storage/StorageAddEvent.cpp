/*
 * Copyright (C) 2018 Burak Akguel, Christian Gesse, Fabian Ruhland, Filip Krakowski, Michael Schoettner
 * Heinrich-Heine University
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "StorageAddEvent.h"

StorageAddEvent::StorageAddEvent() : Event(TYPE) {

}

StorageAddEvent::StorageAddEvent(StorageDevice *device) : Event(TYPE) {
    this->device = device;
}

StorageAddEvent::StorageAddEvent(const StorageAddEvent &other) : Event(other){
    this->device = other.device;
}

char *StorageAddEvent::getName() {
    return const_cast<char *>("StorageAddEvent");
}

StorageDevice* StorageAddEvent::getDevice() {
    return device;
}
