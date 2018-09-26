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

#ifndef __BlueScreen_include__
#define __BlueScreen_include__

#include <kernel/threads/ThreadState.h>
#include <lib/OutputStream.h>
#include "kernel/memory/MemLayout.h"

class BlueScreen : public OutputStream {

public:

    BlueScreen() = default;

    BlueScreen(const BlueScreen &other) = delete;

    BlueScreen &operator=(const BlueScreen &other) = delete;

    /**
     * Initializes the bluescreen.
     */
    void initialize();

    /**
     * Prints out the bluescreen containing debug information.
     *
     * @param frame The interrupt frame.
     */
    void print(InterruptFrame &frame);

    void flush() override;

    static void setErrorMessage(const char *message);

private:

    int x = 0;

    int y = 0;

    static const char *errorMessage;

    void show(uint16_t x, uint16_t y, char c);

    const uint8_t ROWS = 25;

    const uint8_t COLUMNS = 80;

    const uint8_t ATTRIBUTE = 0x1F;

    const char *CGA_START = reinterpret_cast<const char *>(VIRT_CGA_START);

    void puts(const char *s, uint32_t n);

    void putc(char c);
};

#endif
