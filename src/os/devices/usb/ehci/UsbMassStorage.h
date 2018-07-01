/*
 * Copyright (C) 2018  Filip Krakowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __UsbMassStorage_include__
#define __UsbMassStorage_include__

#include "lib/lock/Spinlock.h"
#include "kernel/services/DebugService.h"
#include "devices/usb/UsbDevice.h"
#include "Scsi.h"

/**
 * @author Filip Krakowski
 */
class UsbMassStorage : public UsbDevice {

public:

    const static uint32_t CBW_SIGNATURE = 0x43425355;
    const static uint32_t CSW_SIGNATURE = 0x53425355;

    typedef struct {
        uint32_t    signature = CBW_SIGNATURE;      // Signature
        uint32_t    tag;                            // Tag
        uint32_t    length;                         // Length
        uint8_t     direction;                      // Direction
        uint8_t     unit;                           // Logical Unit Number
        uint8_t     cmdLength;                      // Command Length
        uint8_t     cmdData[16];                    // Command Data
    } CommandBlockWrapper;

    typedef struct {
        uint32_t    signature = CSW_SIGNATURE;      // Signature
        uint32_t    tag;                            // Tag
        uint32_t    dataResidue;                    // Data Residue
        uint8_t     status;                         // Status
    } CommandStatusWrapper;

    UsbMassStorage(AsyncListQueue::QueueHead *control, uint8_t portNumber);

    static CommandBlockWrapper getScsiInquiry();
    static CommandBlockWrapper testUnitReady();
    static CommandBlockWrapper readCapacity();
    static CommandBlockWrapper read(uint32_t blockHigh, uint32_t blockLow, uint32_t length);
    static CommandBlockWrapper write(uint32_t blockHigh, uint32_t blockLow, uint32_t length);
    static CommandBlockWrapper requestSense();

    UsbDevice::Status readData(uint32_t blockHigh, uint32_t blockLow, uint32_t blocks, uint8_t *buffer);
    UsbDevice::Status writeData(uint32_t blockHigh, uint32_t blockLow, uint32_t blocks, uint8_t *buffer);

private:

    static Logger &log;

    DebugService *debugService;

    char scsiVendor[9];
    char scsiProduct[17];
    char scsiRevision[5];

    uint8_t maxLun;

    uint32_t capacity;

    AsyncListQueue::QueueHead *bulkIn;
    AsyncListQueue::QueueHead *bulkOut;

    bool bulkInToggle;
    bool bulkOutToggle;

    Scsi::InquiryData inquiryData;

    void init();

    Scsi::InquiryData getInquiryData();

    UsbDevice::Status bulkReset(uint16_t interface);

    UsbDevice::Status testUnityReady();

    UsbDevice::Status getCapacity();

    UsbDevice::Status getSense();

    void printCommandBlockWrapper(UsbMassStorage::CommandBlockWrapper *commandBlockWrapper);
    void printCommandStatusWrapper(UsbMassStorage::CommandStatusWrapper *commandStatusWrapper);

    uint8_t getMaxLun(uint16_t interface);
};

#endif