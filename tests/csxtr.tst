# This test file was generated from offline assembler source
# by bldhtc.rexx  5 Jun 2016 09:38:33
# Treat as object code.  That is, modifications will be lost.
# assemble and listing files are provided for information only.
*Testcase csxtr csdtr cxstr cxutr 20160605 09.38
sysclear
archlvl z
r    1A0=00000001800000000000000000000200
r    1C0=00020001800000000000000000000000
r    1D0=00020001800000000000000000000000
*Program 7
r    200=B3EB0040B600F3509604F351B700F350
r    210=6800F3586820F360B3EB0040EB45F310
r    220=0024ED00001F00496000F3006020F308
r    230=B3EA00404050F320
r    238=6840F368B3E30064E360F3280024EB45
r    248=F3100004B3FB00046000F3306020F338
r    258=EB550004000CB3FA00046000F3406020
r    268=F34812EE077E0AFF
r    358=2608134B9C1E28E56F3C127177823534
r    368=263934B9C1E28E56
runtest .1
runtest program .1
*Compare
r 300.10
r 310.10
*Want "csxtr/srxt low" 45678901 23456789 01234567 8901234C
r 320.2
*Want "csxtr/srxt high" 0123
r 328.8
*Want "csdtr" 23456789 0123456C
r 330.10
*Want "cxstr" 2208004B 9C1E28E5 6F3C1271 77823534
r 340.10
*Want "cxutr" 2208045D E08D4D2E 70781271 77823534
*Done
