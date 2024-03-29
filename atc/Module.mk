################ Source files ##########################################

atc/NAME	:= atc
atc/EXE		:= $Oatc/${atc/NAME}
atc/SRCS	:= $(wildcard atc/*.c)
atc/OBJS	:= $(addprefix $O,$(atc/SRCS:.c=.o))
atc/DEPS	:= $(atc/OBJS:.o=.d)
atc/LIBS	:= ${CURSES_LIBS} ${MATH_LIBS}

################ Compilation ###########################################

.PHONY:	atc/all atc/clean atc/run atc/install atc/uninstall

all:		atc/all
atc/all:	${atc/EXE}
atc/run:	${atc/EXE}
	@${atc/EXE}

${atc/EXE}:	${atc/OBJS}
	@echo "Linking $@ ..."
	@${CC} ${LDFLAGS} -o $@ ${atc/OBJS} ${atc/LIBS}

################ Installation ##########################################

ifdef BINDIR
atc/EXEI	:= ${BINDIR}/${atc/NAME}
atc/MANI	:= ${MANDIR}/man6/${atc/NAME}.6.gz
atc/SCOREI	:= ${STATEDIR}/atc_score

install:		atc/install
atc/install:	${atc/EXEI} ${atc/MANI} ${atc/SCOREI}
${atc/EXEI}:	${atc/EXE}
	@echo "Installing $@ ..."
	@${INSTALLEXE} $< $@
${atc/MANI}:	atc/${atc/NAME}.6
	@echo "Installing $@ ..."
	@gzip -9 -c $< > $@ && chmod 644 $@
${atc/SCOREI}:
	@echo "Creating initial score file $@ ..."
	@${INSTALLSCORE} /dev/null $@

uninstall:		atc/uninstall
atc/uninstall:
	@if [ -f ${atc/EXEI} ]; then\
	    echo "Removing ${atc/EXEI} ...";\
	    rm -f ${atc/EXEI} ${atc/MANI} ${atc/SCOREI};\
	fi
endif

################ Maintenance ###########################################

clean:	atc/clean
atc/clean:
	@if [ -d $O/atc ]; then\
	    rm -f ${atc/EXE} ${atc/OBJS} ${atc/DEPS} $Oatc/.d;\
	    rmdir $O/atc;\
	fi

$Oatc/.d:	$O.d
	@[ -d $Oatc ] || mkdir $Oatc && touch $Oatc/.d

${atc/OBJS}: ${CONFS} atc/Module.mk $Oatc/.d

-include ${atc/DEPS}
