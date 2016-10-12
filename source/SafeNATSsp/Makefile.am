##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_LDFLAGS = -lccsp_common
#AM_LDFLAGS = -ltr181

AM_CPPFLAGS = -Wall -Werror
ACLOCAL_AMFLAGS = -I m4
hardware_platform = i686-linux-gnu

lib_LTLIBRARIES = libSafeNATSsp.la
libSafeNATSsp_la_CPPFLAGS = -I$(top_srcdir)/source/SafeNATCore -I$(top_srcdir)/source/SafeNATSsp -I$(top_srcdir)/include $(CPPFLAGS)

if CCSP_ARCH_ARM
AM_CFLAGS += -D_ANSC_LITTLE_ENDIAN_
libSafeNATSsp_la_CPPFLAGS += -I$(top_srcdir)/source-arm/SafeNAT/board_sbapi -I$(top_srcdir)/source-arm/SafeNAT/board_ml/
endif

if CCSP_ARCH_ATOM
libSafeNATSsp_la_CPPFLAGS += -I$(top_srcdir)/source-atom/SafeNAT/board_sbapi -I$(top_srcdir)/source-atom/SafeNAT/board_ml/
endif

libSafeNATSsp_la_SOURCES = ssp_messagebus_interface.c ssp_main.c ssp_action.c plugin_main.c cosa_safenat_internal.c cosa_safenat_dml.c safenat_portmapping_rules.c

libSafeNATSsp_la_LDFLAGS = -lccsp_common -ldl -rdynamic $(SYSTEMD_LDFLAGS)

