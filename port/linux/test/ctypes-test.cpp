#include "gtest/gtest.h"
#include "test_common.h"
extern "C" {
#include "PikaMain.h"
#include "PikaParser.h"
#include "PikaStdLib_MemChecker.h"
#include "PikaVM.h"
#include "dataArgs.h"
#include "dataMemory.h"
#include "dataStrs.h"
#include "pikaScript.h"
#include "pika_config_gtest.h"
}

extern PikaMemInfo pikaMemInfo;
/* the log_buff of printf */
extern char log_buff[LOG_BUFF_MAX][LOG_SIZE];

TEST(ctypes, test1) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
        "read_data = ctypes.c_buffer(b'', 16)\n"
        "print(\"----read size----\")\n"
        "datalen = len(read_data.raw)\n"
        "print(datalen)\n"
        "print(read_data.raw)\n"
        "print(\"----read data----\")\n"
        "for i in range(0,datalen):\n"
        "    print(read_data.raw[i])\n"
        "\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[67], "16\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(ctypes, test2) {
    /* init */
    pikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    obj_run(pikaMain,
    "len(b'test\\x0')\n"
    "len(str(b'test\\x0'))\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "4\r\n");
    EXPECT_STREQ(log_buff[1], "5\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}