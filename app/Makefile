include ../config.mk

EXEC_NAME=pstate-frequency
OBJECTS=$(patsubst src/%.cpp,obj/%.o,$(wildcard src/*.cpp))
TARGET=bin/$(EXEC_NAME)

RES_DIR=res
SYSTEM_PREFIX=/usr
BASH_COMP_DIR=share/bash-completion/completions
ZSH_COMP_DIR=share/zsh/site-functions
SYSTEMD_UNIT_DIR=lib/systemd/system
UDEV_RULES_DIR=lib/udev/rules.d

UDEV=99-$(EXEC_NAME).rules
SYSTEMD=$(EXEC_NAME).service
SYSTEMD_SLEEP=$(EXEC_NAME)-sleep.service
X86_NAME=x86_energy_perf_policy
X86_SLEEP=x86_energy_perf_policy-sleep.service

.PHONY: all dirs clean install-app uninstall-app install-res install-bash \
	install-zsh install-udev install-systemd uninstall-res uninstall-bash \
	uninstall-zsh uninstall-udev uninstall-systemd

all: $(TARGET)

$(OBJECTS): | obj

obj:
	@mkdir -p $@

obj/%.o : src/%.cpp
	@echo "  CXX  $@"
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

$(TARGET): dirs $(OBJECTS)
	@echo "  LD   $@"
	@$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

dirs:
	@mkdir -p obj
	@mkdir -p bin

clean:
	@rm -rf $(TARGET) $(OBJECTS) obj bin
	@echo "  CLEAN PROJECT"

install-app: all
	@echo "  INSTALL  $(DESTDIR)$(PREFIX)/$(TARGET)"
	@install -d $(DESTDIR)$(PREFIX)/bin
	@install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin

uninstall-app:
	@echo "  UNINSTALL  $(DESTDIR)$(PREFIX)/bin/$(EXEC_NAME)"
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(EXEC_NAME)

install-res:
ifeq ($(INCLUDE_BASH_COMPLETION), 1)
	@$(MAKE) install-bash
endif
ifeq ($(INCLUDE_ZSH_COMPLETION), 1)
	@$(MAKE) install-zsh
endif
ifeq ($(INCLUDE_UDEV_RULE), 1)
	@$(MAKE) install-udev
endif
ifeq ($(INCLUDE_SYSTEMD_UNIT), 1)
	@$(MAKE) install-systemd
endif

install-bash:
	@echo -n "  INSTALL  "
	@echo "$(DESTDIR)$(SYSTEM_PREFIX)/$(BASH_COMP_DIR)/$(EXEC_NAME)"
	@install -d $(DESTDIR)$(SYSTEM_PREFIX)/$(BASH_COMP_DIR)
	@install -m 644 $(RES_DIR)/shell/bash/bash_completion \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(BASH_COMP_DIR)/$(EXEC_NAME)

install-zsh:
	@echo -n "  INSTALL  "
	@echo "$(DESTDIR)$(SYSTEM_PREFIX)/$(ZSH_COMP_DIR)/_$(EXEC_NAME)"
	@install -d $(DESTDIR)$(SYSTEM_PREFIX)/$(ZSH_COMP_DIR)
	@install -m 644 $(RES_DIR)/shell/zsh/zsh_completion \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(ZSH_COMP_DIR)/_$(EXEC_NAME)

install-udev:
	@echo "  INSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(UDEV_RULES_DIR)/$(UDEV)"
	@install -d $(DESTDIR)$(SYSTEM_PREFIX)/$(UDEV_RULES_DIR)
	@install -m 644 $(RES_DIR)/udev/$(UDEV) \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(UDEV_RULES_DIR)/$(UDEV)
	@sed -i "s#$(EXEC_NAME)#$(PREFIX)/bin/$(EXEC_NAME)#g" \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(UDEV_RULES_DIR)/$(UDEV)

install-systemd:
	@echo "  INSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD)"
	@install -d $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)
	@install -m 644 $(RES_DIR)/systemd/$(SYSTEMD) \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD)
	@sed -i "s#$(EXEC_NAME)#$(PREFIX)/bin/$(EXEC_NAME)#g" \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD)
	@echo "  INSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD_SLEEP)"
	@install -m 644 $(RES_DIR)/systemd/$(SYSTEMD_SLEEP) \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD_SLEEP)
	@sed -i "s#$(EXEC_NAME)#$(PREFIX)/bin/$(EXEC_NAME)#g" \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD_SLEEP)
	@echo "  INSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(X86_SLEEP)"
	@install -m 644 $(RES_DIR)/systemd/$(X86_SLEEP) \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(X86_SLEEP)
	@sed -i "s#$(X86_NAME)#$(PREFIX)/bin/$(X86_NAME)#g" \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(X86_SLEEP)
ifeq ($(X86_ENERGY_PERF_POLICY), 0)
	@sed -i "s#-v normal#-v powersave#g" \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(X86_SLEEP)
else ifeq ($(X86_ENERGY_PERF_POLICY), 2)
	@sed -i "s#-v normal#-v performance#g" \
		$(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(X86_SLEEP)

endif

uninstall-res:
ifeq ($(INCLUDE_BASH_COMPLETION), 1)
	@$(MAKE) uninstall-bash
endif
ifeq ($(INCLUDE_ZSH_COMPLETION), 1)
	@$(MAKE) uninstall-zsh
endif
ifeq ($(INCLUDE_UDEV_RULE), 1)
	@$(MAKE) uninstall-udev
endif
ifeq ($(INCLUDE_SYSTEMD_UNIT), 1)
	@$(MAKE) uninstall-systemd
endif

uninstall-bash:
	@echo -n "  UNINSTALL  "
	@echo "$(DESTDIR)$(SYSTEM_PREFIX)/$(BASH_COMP_DIR)/$(EXEC_NAME)"
	@rm -f $(DESTDIR)$(SYSTEM_PREFIX)/$(BASH_COMP_DIR)/$(EXEC_NAME)

uninstall-zsh:
	@echo -n "  UNINSTALL  "
	@echo "$(DESTDIR)$(SYSTEM_PREFIX)/$(ZSH_COMP_DIR)/_$(EXEC_NAME)"
	@rm -f $(DESTDIR)$(SYSTEM_PREFIX)/$(ZSH_COMP_DIR)/_$(EXEC_NAME)

uninstall-udev:
	@echo "  UNINSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(UDEV_RULES_DIR)/$(UDEV)"
	@rm -f $(DESTDIR)$(SYSTEM_PREFIX)/$(UDEV_RULES_DIR)/$(UDEV)

uninstall-systemd:
	@echo "  UNINSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD)"
	@rm -f $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD)
	@echo "  UNINSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD_SLEEP)"
	@rm -f $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(SYSTEMD_SLEEP)
	@echo "  UNINSTALL  $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(X86_SLEEP)"
	@rm -f $(DESTDIR)$(SYSTEM_PREFIX)/$(SYSTEMD_UNIT_DIR)/$(X86_SLEEP)

