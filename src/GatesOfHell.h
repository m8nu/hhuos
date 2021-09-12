/*
 * Copyright (C) 2018-2021 Heinrich-Heine-Universitaet Duesseldorf,
 * Institute of Computer Science, Department Operating Systems
 * Burak Akguel, Christian Gesse, Fabian Ruhland, Filip Krakowski, Michael Schoettner
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

#ifndef __KernelEntry_include__
#define __KernelEntry_include__

#include <kernel/log/Logger.h>
#include <lib/util/stream/PrintWriter.h>
#include <lib/util/stream/Reader.h>

/**
 * Represents the entry point for the operating system.
 */
class GatesOfHell {

public:
    /**
     * Default-constructor.
     * Deleted, as this class has only static members.
     */
    GatesOfHell() = delete;

    /**
     * Copy constructor.
     */
    GatesOfHell(const GatesOfHell &other) = delete;

    /**
     * Assignment operator.
     */
    GatesOfHell &operator=(const GatesOfHell &other) = delete;

    /**
     * Destructor.
     */
    ~GatesOfHell() = delete;

    /**
     * Entry point for the operating system.
     * This method is invoked by the main() method, after boot strapping process is finished an paging is setup.
     */
    [[noreturn]] static void enter();

private:

    static void enableSerialLogging();

    static void initializeKeyboard();

    static void initializeFilesystem();

    static void initializeTerminal();

    static void initializeHeadlessMode();

    static void printBanner();

    static void printBannerLine(Util::Stream::PrintWriter &writer, Util::Stream::Reader &reader);

    static void printDefaultBanner(Util::Stream::PrintWriter &writer);

    static void colorTest(Util::Stream::PrintWriter &writer);

    static Kernel::Logger log;
    static Util::Stream::InputStream *inputStream;
    static Util::Stream::OutputStream *outputStream;

};


#endif
