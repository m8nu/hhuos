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

#include <kernel/Kernel.h>
#include <kernel/services/InputService.h>
#include <kernel/services/TimeService.h>
#include <kernel/services/SoundService.h>
#include <kernel/threads/WorkerThread.h>
#include "apps/game/HHUEngine.h"

Random HHUEngine::random(42, 32768);
Game* HHUEngine::currentGame;

uint32_t hhu_engine_beep(const Util::Pair<float, uint32_t> &data) {
    Kernel::getService<SoundService>()->getPcSpeaker()->play(data.first, data.second);

    return 0;
}

bool HHUEngine::isKeyPressed(int scancode){


    return Kernel::getService<InputService>()->getKeyboard()->isKeyPressed(scancode);
}

unsigned long HHUEngine::time(){
    return Kernel::getService<TimeService>()->getSystemTime();
}

float HHUEngine::rand(){
    return random.rand(32768) / 32768.0f; // [0 .. 0,999]
}

void HHUEngine::setSeed(unsigned int seed){
    random.setSeed(seed);
}

void HHUEngine::beep(float frequency, uint32_t length) {
    Kernel::getService<SoundService>()->getPcSpeaker()->play(frequency, length);
    /*const Util::Pair<float, uint32_t> data(frequency, length);

    auto *beepThread = new WorkerThread<Util::Pair<float, uint32_t>, uint32_t >(hhu_engine_beep, data, nullptr);

    beepThread->start();*/
}

void HHUEngine::setCurrentGame(Game* game){
    currentGame = game;
}

bool HHUEngine::isGameSet(){
    return currentGame != nullptr;
}

void HHUEngine::instantiate(GameObject* gameObject){
    currentGame->addGameObject(*gameObject);
}

void HHUEngine::destroy(GameObject* gameObject){
    currentGame->removeGameObject(*gameObject);
}

int HHUEngine::strLen(char* string){
    return strlen(string);
}

bool HHUEngine::strEqual(char* s1, char* s2){
    return strcmp(s1, s2) == 0;
}
