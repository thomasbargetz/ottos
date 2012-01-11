#include <ottos/system.h>
#include <ottos/kernel.h>
#include <ottos/const.h>
#include <ottos/timer.h>

#include "../../bin/led_test.h"
#include "../../bin/serial_test.h"
#include "../../bin/uptime_test.h"
#include "../../bin/i2c_test.h"
#include "../../bin/video_test.h"
#include "../drivers/i2c/i2c.h"

#include "kernel/intc/irq.h"
#include "kernel/pm/process.h"
#include "dev/devices.h"
#include "../hal/uart.h"

#include "../fs/fs.h"
#include "../tty/tty.h"

#include "../fs/vfat/fat_filelib.h"
#include "../../drivers/mmchs/mmchs.h"

#include "kernel/mmu/mmu.h"
#include "../lib/ottos/parser.h"
#include "kernel/loader/loader.h"

void devices_test() {
	devices_init();
}

static void loop_forever() {
  for (;;)
    ;
}

void i2c_test() {
  //devices_init();

	i2c_init();
	pulse_leds();
}

void mmu_test() {
	devices_init();
	irq_enable();

	mmu_init();

	process_table_init();
	//process_create(1, (int) toggle_led1);
	//process_create(1, (int) toggle_led2);

	irq_init();
	timer_init();
	irq_register_context_switch();

	kernel_to_user_mode();
}

// MMU TEST SYSCALLS
//#define byte0 ":020000040002F8:20000000000029F090012D8C01087C0104003B0400FBF0110403070403040404FB04030194:200080000101FB0304020400EA1EFFFFFF1401000000041EFF3000B2000C0400040800031A:20010000040023B20100240484EF30010014040E011C200800000001002C006B00F700003F:20018000000A000001EFA0001E01032B032F10081010181810FB1010010C0D0C1003040472:20020000010608080102080801010402010101B2B20100B2B20101010101010103F90113C9:2002800002CB040704B423B204F9040102B2B202010101010409040423032302230104F50E:200300000401010101FB01780C0038A1C00002000120022002A020201CA0172012A00D20C3:2003800008A0038203820203028203820203028203820203028203820203020222E4038EE1:0704000000000C1E000C1EA1:00000001FF"
//#define byte1 ":020000040002F8:200000000000004000000000000050000000004000FF80001000002000303020FF20003092:200080003020FF2020002000FFFFFFFFFFC0000010001000FF4050C0400001001020000016:20010000001000C00048480001FF800000FFC040E0FF4740C0C0C0C0C010000000FFC0C04B:200180001000203000FF8600FF400000000000000020505020FF002080300020C0F130305B:200200008000101080005050802030F23030803030800030303030803030208000FF00005D:2002800000FF20003030383020FF008020303020203030802000303034303430343020FF6D:200300002080303020FF8047400000E0E00031102008280424000001000100020002000335:200380000003000330030330030230020230020130010130010030000030000024FF10E0AF:07040000100040FF0040FF67:00000001FF"
//#define byte2 ":020000040002F8:200000000000002D9F70009F70009F750000009554FFBD009011005200908152FF9200D025:20008000C152FF1062809052FF2FFFFFFF9F7CA0A09C8C00FF2DA0D5A00080858091520023:20010000919100D584A0A05CA0FFBD14002FA0A08F2FC02DA08D9D8C8D9F9D0050FFA08DA3:20018000A0A0A0A000FF01522F2D1100100052002D42B1A052FFBD92BD1200D24F8C9180D1:20020000BD00B1A0BD00B1A0BD524F83D1C0BDD1C0BDA0D1C0D1C0BDD1C052BD11FF100006:2002800010FF520091C0A04052FF72BD92D1C04292D1C0BD520091C0A040A040A04052FF73:2003000092BDD1C052FFBDC02D5100A03E601161B052A052A0520052005200520052005281:2003800000520050A34050A34050A34050A34050A34050A34050A34050A34051A0FFA0B033:070400006360BD2FA0BD2FBA:00000001FF"
//#define byte3 ":020000040002F8:2000000010EBEBE9E5E31BE5E31BE5E30AEAEBE4E31AE8EAE4E31AE24AE4E4E25AE20AE410:20008000E4E21AE21210E4E31AE1FFFFFFE5E303011512EAFFE9E1E1E3EAE0E0E2E5E30AF5:20010000E5E5EBE1E2E1E1E1E1CAE8E31AE1E1E1E2E146E9E3E5E5E2E5E5E5EBE31AE3E5B1:20018000E3E3E3E3EFEA00E301E9E31AE31AE33AE9E2E8E8E22AE8E208E20AE3E2E0E4E444:2002000008EAE8E808EAE8E808E21210E4E4E8E0E0E8E1E0E0E4E4E8E4E4E208E31AE31AF9:20028000E30AE23AE4E0E1E1E22AE308E2202022E22424E8E23AE4E4E1E5E1E5E1E5E22A40:20030000E208E4E4E21AE846E9E30AE1E042E212E1E191E191E18AE18AE18AE18AE18AE177:200380008AE18AE1E020E1E020E1E020E1E020E1E020E1E020E1E020E1E020E1313AE1E152:070400004222E8E1E3E8E11C:00000001FF"

// LED APP
#define byte0 ":020000040002F8:20000000000029F090012D8C01087C0104003B0400FBF0110403070403040404FB04030194:200080000101FB0304020400EA1EFFFFFF1401000000041EFF3000B2000C0400040800031A:20010000040037B20100240484EF30010014040E011C200C0000000402000B0001000100A3:2001800060007800F7000A00000104000201040100040B050401010000E2A0001E01032B90:20020000032F10081010181810FB1010010C0D0C10030404010608080102080801010402A6:20028000010101B2B20100B2B20101010101010103F9011302CB040704B423B204F9040114:2003000002B2B202010101010409040423032302230104F50401010101FB01780C0038A193:20038000C00002000120022002A020201CA0172012A00D2008A003820382020302820382E4:1B0400000203028203820203028203820203020222E4038E00000C1E000C1ED1:00000001FF"
#define byte1 ":020000040002F8:200000000000004000000000000050000000004000FF80001000002000303020FF20003092:200080003020FF2020002000FFFFFFFFFFC0000010001000FF4050C0400001001020000016:20010000001000C00048480001FF800000FFC040E0FF4740C0C0C0C00020103000C0C0C0FA:2001800010000000FF1000203000C00000C0C000C0C01000302000C0C0FF8600FF4000008C:20020000000000000020505020FF002080300020C0F130308000101080005050802030F27C:200280003030803030800030303030803030208000FF000000FF20003030383020FF0080D9:2003000020303020203030802000303034303430343020FF2080303020FF8047400000E06C:20038000E00031102008280424000001000100020002000300030003300303300302300218:1B0400000230020130010130010030000030000024FF10E0100040FF0040FF48:00000001FF"
#define byte2 ":020000040002F8:200000000000002D9F70009F70009F750000009554FFBD009011005200908152FF9200D025:20008000C152FF1062809052FF2FFFFFFF9F7CA0A09C8C00FF2DA0D5A00080858091520023:20010000919100D584A0A05CA0FFBD14002FA0A08F2FC02DA08DA0CDA0A0A0A0009D8C8D6E:200180009F9D0050FFA0A0A0A000DD5C00A0CD00A0CDA0A0DDA000A08DFF01522F2D110098:20020000100052002D42B1A052FFBD92BD1200D24F8C9180BD00B1A0BD00B1A0BD524F8392:20028000D1C0BDD1C0BDA0D1C0D1C0BDD1C052BD11FF100010FF520091C0A04052FF72BD71:2003000092D1C04292D1C0BD520091C0A040A040A04052FF92BDD1C052FFBDC02D5100A038:200380003E601161B052A052A0520052005200520052005200520050A34050A34050A340E2:1B04000050A34050A34050A34050A34050A34051A0FFA0B06360BD2FA0BD2F67:00000001FF"
#define byte3 ":020000040002F8:2000000010EBEBE9E5E31BE5E31BE5E30AEAEBE4E31AE8EAE4E31AE24AE4E4E25AE20AE410:20008000E4E21AE21210E4E31AE1FFFFFFE5E303011512EAFFE9E1E1E3EAE0E0E2E5E30AF5:20010000E5E5EBE1E2E1E1E1E1CAE8E31AE1E1E1E2E146E9E3E5E3E5E3E3E3E3EFE5E2E5E8:20018000E5E5EBE31AE3E3E3E3EFE5E31AE3E5EAE3E5E3E3E5E3EFE3E5EA00E301E9E31ADD:20020000E31AE33AE9E2E8E8E22AE8E208E20AE3E2E0E4E408EAE8E808EAE8E808E2121062:20028000E4E4E8E0E0E8E1E0E0E4E4E8E4E4E208E31AE31AE30AE23AE4E0E1E1E22AE30883:20030000E2202022E22424E8E23AE4E4E1E5E1E5E1E5E22AE208E4E4E21AE846E9E30AE1B2:20038000E042E212E1E191E191E18AE18AE18AE18AE18AE18AE18AE1E020E1E020E1E020F2:1B040000E1E020E1E020E1E020E1E020E1E020E1313AE1E14222E8E1E3E8E195:00000001FF"

// PRINT APP
//#define byte0_ ":020000040002F8:20000000000029F090012D8C01087C0104003B0400FBF0110403070403040404FB04030194:200080000101FB0304020400EA1EFFFFFF1401000000041EFF3000B2000C0400040800031A:20010000040027B20100240484EF30010014040E011C200C0000440004000000306D0004DD:200180000404C60000000100F1CC40001E01032B032F10081010181810FB1010010C0D0C5B:2002000010030404010608080102080801010402010101B2B20100B2B201010101010101BE:2002800003F9011302CB040704B423B204F9040102B2B2020101010104090404230323021B:20030000230104F50401010101FB01780C0038A1C00002000120022002A020201CA0172085:2003800012A00D2008A0038203820203028203820203028203820203028203820203020299:2004000022E4038E00000C1E000C1E00000100000100000008000001000E080400080004C0:1304800009010E00000A000001000C04000004000B010C1A:0104CC0074BB:00000001FF"
//#define byte1_ ":020000040002F8:200000000000004000000000000050000000004000FF80001000002000303020FF20003092:200080003020FF2020002000FFFFFFFFFFC0000010001000FF4050C0400001001020000016:20010000001000C00048480001FF800000FFC040E0FF4740C0C0C0C0C0C0C000100000004A:20018000100000C0C0C0C0C0FF044200FF400000000000000020505020FF0020803000203C:20020000C0F130308000101080005050802030F2303080303080003030303080303020804B:2002800000FF000000FF20003030383020FF008020303020203030802000303034303430F1:20030000343020FF2080303020FF8047400000E0E0003110200828042400000100010002B7:200380000002000300030003300303300302300202300201300101300100300000300000BD:2004000024FF10E0100040FF0040FF4010002030008040100020300080402010003010202B:130480000000804010002030008040100010203000008099:0104CC0065CA:00000001FF"
//#define byte2_ ":020000040002F8:200000000000002D9F70009F70009F750000009554FFBD009011005200908152FF9200D025:20008000C152FF1062809052FF2FFFFFFF9F7CA0A09C8C00FF2DA0D5A00080858091520023:20010000919100D584A0A05CA0FFBD14002FA0A08F2FC02DA08D9F9C8DA08D9D9F00500090:200180008DA000A08D9D8C8DFF020F522F2D1100100052002D42B1A052FFBD92BD1200D21D:200200004F8C9180BD00B1A0BD00B1A0BD524F83D1C0BDD1C0BDA0D1C0D1C0BDD1C052BD3A:2002800011FF100010FF520091C0A04052FF72BD92D1C04292D1C0BD520091C0A040A04084:20030000A04052FF92BDD1C052FFBDC02D5100A03E601161B052A052A052005200520052F4:200380000052005200520050A34050A34050A34050A34050A34050A34050A34050A340517E:20040000A0FFA0B06360BD2FA0BD2F2DA0A0A0A000BD2DA0A0A0A000BD2D8D8D8D9D9D9D33:13048000A000BD2DA0A0A0A000BD2D8D8D9D9DA0A000BD24:0104CC0073BC:00000001FF"
//#define byte3_ ":020000040002F8:2000000010EBEBE9E5E31BE5E31BE5E30AEAEBE4E31AE8EAE4E31AE24AE4E4E25AE20AE410:20008000E4E21AE21210E4E31AE1FFFFFFE5E303011512EAFFE9E1E1E3EAE0E0E2E5E30AF5:20010000E5E5EBE1E2E1E1E1E1CAE8E31AE1E1E1E2E146E9E3E5E5E5E5E3E5E5E5EBE30ABE:20018000E2E3EBE3E5E5E2E5EA0000E301E9E31AE31AE33AE9E2E8E8E22AE8E208E20AE325:20020000E2E0E4E408EAE8E808EAE8E808E21210E4E4E8E0E0E8E1E0E0E4E4E8E4E4E20869:20028000E31AE31AE30AE23AE4E0E1E1E22AE308E2202022E22424E8E23AE4E4E1E5E1E518:20030000E1E5E22AE208E4E4E21AE846E9E30AE1E042E212E1E191E191E18AE18AE18AE17B:200380008AE18AE18AE18AE1E020E1E020E1E020E1E020E1E020E1E020E1E020E1E020E1A9:20040000313AE1E14222E8E1E3E8E1E9E3E3E3E3EFE8E9E3E3E3E3EFE8E9E5E5E5E5E5E5F7:13048000E3EFE8E9E3E3E3E3EFE8E9E5E5E5E5E3E3EFE849:0104CC0074BB:00000001FF"

//// EXIT APP
#define byte0_ ":020000040002F8:20000000000029F090012D8C01087C0104003B0400FBF0110403070403040404FB04030194:200080000101FB0304020400EA1EFFFFFF1401000000041EFF3000B2000C0400040800031A:20010000040019B20100240484EF30010014040E011C2008180000040D81000894001E0173:20018000032B032F10081010181810FB1010010C0D0C1003040401060808010208080101FF:200200000402010101B2B20100B2B20101010101010103F9011302CB040704B423B204F993:20028000040102B2B202010101010409040423032302230104F50401010101FB010000016B:2003000000000100000008000001000E08040008000409010E00000A000001000C0400007A:0503800004000B010C5C:0103940074F4:00000001FF"
#define byte1_ ":020000040002F8:200000000000004000000000000050000000004000FF80001000002000303020FF20003092:200080003020FF2020002000FFFFFFFFFFC0000010001000FF4050C0400001001020000016:20010000001000C00048480001FF800000FFC040E0FF4740C0C0C000100000800300FF4088:200180000000000000000020505020FF002080300020C0F13030800010108000505080201F:2002000030F23030803030800030303030803030208000FF000000FF20003030383020FFB7:20028000008020303020203030802000303034303430343020FF2080303020FF8040100084:2003000020300080401000203000804020100030102000008040100020300080401000101D:050380002030000080A8:010394006503:00000001FF"
#define byte2_ ":020000040002F8:200000000000002D9F70009F70009F750000009554FFBD009011005200908152FF9200D025:20008000C152FF1062809052FF2FFFFFFF9F7CA0A09C8C00FF2DA0D5A00080858091520023:20010000919100D584A0A05CA0FFBD14002FA0A08F2FC02D9F9C8DA0A000A0BD02522F2D29:200180001100100052002D42B1A052FFBD92BD1200D24F8C9180BD00B1A0BD00B1A0BD52D4:200200004F83D1C0BDD1C0BDA0D1C0D1C0BDD1C052BD11FF100010FF520091C0A04052FF4E:2002800072BD92D1C04292D1C0BD520091C0A040A040A04052FF92BDD1C052FFBD2DA0A0FB:20030000A0A000BD2DA0A0A0A000BD2D8D8D8D9D9D9DA000BD2DA0A0A0A000BD2D8D8D9D20:050380009DA0A000BDDE:0103940073F5:00000001FF"
#define byte3_ ":020000040002F8:2000000010EBEBE9E5E31BE5E31BE5E30AEAEBE4E31AE8EAE4E31AE24AE4E4E25AE20AE410:20008000E4E21AE21210E4E31AE1FFFFFFE5E303011512EAFFE9E1E1E3EAE0E0E2E5E30AF5:20010000E5E5EBE1E2E1E1E1E1CAE8E31AE1E1E1E2E146E9E5E5E5E3E1EBE3E800E301E9A9:20018000E31AE31AE33AE9E2E8E8E22AE8E208E20AE3E2E0E4E408EAE8E808EAE8E808E208:200200001210E4E4E8E0E0E8E1E0E0E4E4E8E4E4E208E31AE31AE30AE23AE4E0E1E1E22ACC:20028000E308E2202022E22424E8E23AE4E4E1E5E1E5E1E5E22AE208E4E4E21AE8E9E3E396:20030000E3E3EFE8E9E3E3E3E3EFE8E9E5E5E5E5E5E5E3EFE8E9E3E3E3E3EFE8E9E5E5E50F:05038000E5E3E3EFE8F6:0103940074F4:00000001FF"

void user_app_test() {
	code_bytes_t code_bytes;

	irq_disable();

	mmu_init();

	//devices_init();
	//process_table_init();
	irq_init();
	timer_init();

	code_bytes.byte_0 = byte0;
	code_bytes.byte_1 = byte1;
	code_bytes.byte_2 = byte2;
	code_bytes.byte_3 = byte3;

	process_create(1, &code_bytes);

  code_bytes.byte_0 = byte0_;
  code_bytes.byte_1 = byte1_;
  code_bytes.byte_2 = byte2_;
  code_bytes.byte_3 = byte3_;

  process_create(1, &code_bytes);

	irq_register_context_switch();
	irq_enable();

	//mmu_init_memory_for_process(process_table[0]);
	//asm(" MOV R0, #131072");
	//asm(" MOV PC, #131072");

	kernel_to_user_mode();

	kernel_print("go\r\n");
}

int main(int argc, char **argv) {
  // these methods has to be called for EVERY test method
  //irq_disable();
  process_table_init();
  devices_init();
  //mmu_init();
  //irq_enable();
  //kernel_to_user_mode();

  // these methods are the specific tests for every module
  //  process_test();
  //  timer_test();
  //  serial_test();
  //  serial_test_calc();
  //  process_exit_test();
  // fs_test();
  //  i2c_test();
  //  uptime_test();
  //  tty_test();
  //  system_time_test();
  //  uptime_test();
  //video_test();
  user_app_test();

  // do an endless loop
  loop_forever();

	return 0;
}
