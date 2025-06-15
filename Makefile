MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

CC = /opt/arm/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc
LDSCRIPT = linker.ld

BINARY = epp

CFLAGS = -std=c11
CFLAGS += -Og -g
CFLAGS += -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes
CFLAGS += -Wshadow -Werror=implicit
CFLAGS += -nostdlib -mcpu=cortex-m4

LDFLAGS = -T $(LDSCRIPT) $(CFLAGS)

LIBS =

SOURCES = \
	src/startup.c \
	src/main.c \
	src/timer.c \
	src/intr.c \
	src/gpio.c

OBJECTS = $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCES)))

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^ $(LIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BINARY) $(OBJECTS)

.PHONY: clean $(SOURCES)
