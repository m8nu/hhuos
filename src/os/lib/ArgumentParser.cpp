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

#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(const String helpText, uint32_t startAt) :
        helpText(helpText), startIndex(startAt) {

}

void ArgumentParser::addParameter(const String &name, const String &abbreviation, bool required) {
    parameters.add(name);
    abbreviationMap.put(abbreviation, name);

    if(required) {
        requiredParameters.add(name);
    }
}

void ArgumentParser::addSwitch(const String &name, const String &abbreviation) {
    switches.add(name);
    abbreviationMap.put(abbreviation, name);
}

const String& ArgumentParser::getErrorString() {
    return errorString;
}

bool ArgumentParser::parse(Util::Array<String> &arguments) {
    namedArguments.clear();
    switchMap.clear();
    unnamedArguments.clear();

    for (uint32_t i = startIndex; i < arguments.length(); i++) {
        String &currentArg = arguments[i];

        if (!currentArg.beginsWith("-") || currentArg == "-") {
            unnamedArguments.add(currentArg);
        } else if(currentArg == "-h" || currentArg =="--help") {
            errorString = helpText;

            return false;
        } else {
            if (abbreviationMap.containsKey(currentArg.substring(1, currentArg.length()))) {
                currentArg = abbreviationMap.get(currentArg.substring(1, currentArg.length()));
            } else {
                if(currentArg.beginsWith("--")) {
                    currentArg = currentArg.substring(2, currentArg.length());
                } else {
                    currentArg = currentArg.substring(1, currentArg.length());
                }
            }

            if(requiredParameters.contains(currentArg)) {
                requiredParameters.remove(currentArg);
            }

            if (parameters.contains(currentArg)) {
                if (i < arguments.length() - 1) {
                    namedArguments.put(currentArg, arguments[++i]);
                } else {
                    errorString = "No value given for parameter '" + currentArg + "'!";

                    return false;
                }
            } else if (switches.contains(currentArg)) {
                switchMap.put(currentArg, true);
            } else {
                errorString = "Unknown parameter '" + currentArg + "'!";

                return false;
            }
        }
    }

    if(!requiredParameters.isEmpty()) {
        errorString = "Missing required parameters: ";

        for(const String &name : requiredParameters) {
            errorString += "'" + name + "' ";
        }

        return false;
    }

    return true;
}

const String ArgumentParser::getNamedArgument(const String &name) {
    if(namedArguments.containsKey(name)) {
        return namedArguments.get(name);
    }

    return "";
}

Util::Array<String> ArgumentParser::getUnnamedArguments() {
    return unnamedArguments.toArray();
}

bool ArgumentParser::checkSwitch(const String &name) {
    if(switchMap.containsKey(name)) {
        return switchMap.get(name);
    }

    return false;
}


