FUNCw = ${FUNC}ws${WS}

COMMON = tools/gentbl.c
COMMONbp = tools/gentbl_bp.c
HEADER = tools/gentbl.h
CFLAGS = -O3


ifeq (${BP}, y)
NN =  tools/format_bp ${FUNCw}_bp.txt ${FUNCw}_bp ${FUNCw}_bp.bin ${FUNCw}_bp.bmp
else
NN =  tools/format ${FUNCw}.txt ${FUNCw} ${FUNCw}.bin ${FUNCw}.bmp
endif

tools = train test 2bin analyze hamW xor
TOOLS = $(addprefix tools/, ${tools})
TARGETS =  ${FUNCw}.tbl ${NN} ${TOOLS}

.PHONY: all

all: ${TARGETS}


#TOOLS
tools/2bin: tools/2bin.c
	${CC} ${CFLAGS} tools/2bin.c -o tools/2bin -lm

tools/analyze: tools/analyze.c
	${CC} ${CFLAGS} tools/analyze.c -o tools/analyze

tools/hamW: tools/hamW.c
	${CC} ${CFLAGS} tools/hamW.c -o tools/hamW

tools/xor: tools/xor.c
	${CC} ${CFLAGS} tools/xor.c -o tools/xor

tools/train: tools/train.c
	${CC} ${CFLAGS} tools/train.c -o tools/train -lfann

tools/test: tools/test.c
	${CC} ${CFLAGS} tools/test.c -o tools/test -lfann -lm



ifeq (${BP}, y)
tools/format_bp: tools/format_bp.c
	${CC} ${CFLAGS} tools/format_bp.c -o tools/format_bp

${FUNCw}_bp: ${FUNC}.c ${COMMONbp} ${HEADER}
	${CC} ${CFLAGS} -D WORD_SIZE=${WS} ${COMMONbp} ${FUNC}.c -o ${FUNCw}_bp

${FUNCw}_bp.txt: ${FUNCw}_bp
	./${FUNCw}_bp ascii > ${FUNCw}_bp.txt

${FUNCw}.tbl: ${FUNCw}_bp.txt
	./tools/format_bp -s ${WS} < ${FUNCw}_bp.txt > ${FUNCw}.tbl -h

${FUNCw}_bp.bin: ${FUNCw}_bp
	./${FUNCw}_bp > ${FUNCw}_bp.bin

${FUNCw}_bp.bmp: tools/2BMP ${FUNCw}_bp.bin
	./tools/2BMP -r 256 -c 16 16 ${FUNCw}_bp.bin
	mv 0_${FUNCw}_bp.bin_bs16_bi0_16x256.bmp ${FUNCw}_bp.bmp

else
tools/format: tools/format.c
	${CC} ${CFLAGS} tools/format.c -o tools/format

${FUNCw}: ${FUNC}.c ${COMMON} ${HEADER}
	${CC} ${CFLAGS} -D WORD_SIZE=${WS} ${COMMON} ${FUNC}.c -o ${FUNCw}

${FUNCw}.txt: ${FUNCw}
	./${FUNCw} ascii > ${FUNCw}.txt

${FUNCw}.tbl: ${FUNCw}.txt
	./tools/format -s ${WS} < ${FUNCw}.txt > ${FUNCw}.tbl -h

${FUNCw}.bin: ${FUNCw}
	./${FUNCw} > ${FUNCw}.bin

${FUNCw}.bmp: tools/2BMP ${FUNCw}.bin
	./tools/2BMP -r 256 -c 16 16 ${FUNCw}.bin
	mv 0_${FUNCw}.bin_bs16_bi0_16x256.bmp ${FUNCw}.bmp

endif



dirs = tbls nets bins bmps logs data txts
clean:
	-rm $(addsuffix /*, $(addprefix ${DIR}/, ${dirs}))
