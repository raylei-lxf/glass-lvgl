include $(TOPDIR)/rules.mk
include $(BUILD_DIR)/kernel.mk
include $(BUILD_DIR)/package.mk

PKG_NAME:=xrm
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR := $(COMPILE_DIR)/$(PKG_NAME)

define Package/$(PKG_NAME)/config
        if PACKAGE_$(PKG_NAME)
                config ENABLE_VIN_ISP
                        bool "Enabel vin isp support"
                        default n
        endif
endef

define Package/$(PKG_NAME)
  SECTION:=gui
  SUBMENU:=Littlevgl
  CATEGORY:=Gui
  DEPENDS:=+libcedarx +libstdcpp +libspeexdsp +libuapi 
  TITLE:= xrm
  MAINTAINER:= xrm
endef

define Package/$(PKG_NAME)/Default
endef

define Package/$(PKG_NAME)/description
  xrm
endef

define Package/$(PKG_NAME)/config
  source "$(SOURCE)/Config.in"
endef

ifeq ($(CONFIG_lvgl),y)
CONFIGURE_PRJ += ./../lvgl
endif

ifeq ($(CONFIG_lv_drivers),y)
CONFIGURE_PRJ += ./../lv_drivers
endif

ifeq ($(CONFIG_lv_examples),y)
CONFIGURE_PRJ += ./../lv_examples
endif

CONFIGURE_PRJ += ./src/public
CONFIGURE_PRJ += ./src/common
#ifeq ($(CONFIG_evba),y)
CONFIGURE_APP += ./src/evba
CONFIGURE_BIN += evba_bin
#endif

define Build/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/src
	$(CP) $(CONFIGURE_PRJ) $(PKG_BUILD_DIR)/src/
	$(CP) $(CONFIGURE_APP) $(PKG_BUILD_DIR)/src/
	$(CP) $(CONFIGURE_APP)/config/* $(PKG_BUILD_DIR)/src/
	$(CP) $(CONFIGURE_APP)/Makefile $(PKG_BUILD_DIR)/src/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/src\
		ARCH="$(TARGET_ARCH)" \
		AR="$(TARGET_AR)" \
		CC="$(TARGET_CC)" \
		CXX="$(TARGET_CXX)" \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" \
		LOCAL_CFLAGS="$(LOCAL_CFLAGS)" \
		INSTALL_PREFIX="$(PKG_INSTALL_DIR)" \
		all
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/res/
	$(INSTALL_DIR) $(1)/usr/res/image/

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/$(CONFIGURE_BIN) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/evba/designer/image/res/* $(1)/usr/res/image/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
