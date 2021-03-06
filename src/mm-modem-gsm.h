/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details:
 *
 * Copyright (C) 2008 - 2009 Novell, Inc.
 * Copyright (C) 2009 Red Hat, Inc.
 */

#ifndef MM_MODEM_GSM_H
#define MM_MODEM_GSM_H

typedef enum {
    MM_MODEM_GSM_MODE_UNKNOWN      = 0x00000000,
    MM_MODEM_GSM_MODE_ANY          = 0x00000001,
    MM_MODEM_GSM_MODE_GPRS         = 0x00000002,
    MM_MODEM_GSM_MODE_EDGE         = 0x00000004,
    MM_MODEM_GSM_MODE_UMTS         = 0x00000008,
    MM_MODEM_GSM_MODE_HSDPA        = 0x00000010,
    MM_MODEM_GSM_MODE_2G_PREFERRED = 0x00000020,
    MM_MODEM_GSM_MODE_3G_PREFERRED = 0x00000040,
    MM_MODEM_GSM_MODE_2G_ONLY      = 0x00000080,
    MM_MODEM_GSM_MODE_3G_ONLY      = 0x00000100,
    MM_MODEM_GSM_MODE_HSUPA        = 0x00000200,
    MM_MODEM_GSM_MODE_HSPA         = 0x00000400,
    MM_MODEM_GSM_MODE_GSM          = 0x00000800,
    MM_MODEM_GSM_MODE_GSM_COMPACT  = 0x00001000,
} MMModemGsmMode;

typedef enum {
    MM_MODEM_GSM_ALLOWED_MODE_ANY          = 0,
    MM_MODEM_GSM_ALLOWED_MODE_2G_PREFERRED = 1,
    MM_MODEM_GSM_ALLOWED_MODE_3G_PREFERRED = 2,
    MM_MODEM_GSM_ALLOWED_MODE_2G_ONLY      = 3,
    MM_MODEM_GSM_ALLOWED_MODE_3G_ONLY      = 4,

    MM_MODEM_GSM_ALLOWED_MODE_LAST = MM_MODEM_GSM_ALLOWED_MODE_3G_ONLY
} MMModemGsmAllowedMode;

typedef enum {
    MM_MODEM_GSM_ACCESS_TECH_UNKNOWN     = 0,
    MM_MODEM_GSM_ACCESS_TECH_GSM         = 1,
    MM_MODEM_GSM_ACCESS_TECH_GSM_COMPACT = 2,
    MM_MODEM_GSM_ACCESS_TECH_GPRS        = 3,
    MM_MODEM_GSM_ACCESS_TECH_EDGE        = 4,  /* GSM w/EGPRS */
    MM_MODEM_GSM_ACCESS_TECH_UMTS        = 5,  /* UTRAN */
    MM_MODEM_GSM_ACCESS_TECH_HSDPA       = 6,  /* UTRAN w/HSDPA */
    MM_MODEM_GSM_ACCESS_TECH_HSUPA       = 7,  /* UTRAN w/HSUPA */
    MM_MODEM_GSM_ACCESS_TECH_HSPA        = 8,  /* UTRAN w/HSDPA and HSUPA */
    MM_MODEM_GSM_ACCESS_TECH_HSPA_PLUS   = 9,  /* UTRAN w/HSPA+ */

    MM_MODEM_GSM_ACCESS_TECH_LAST = MM_MODEM_GSM_ACCESS_TECH_HSPA_PLUS
} MMModemGsmAccessTech;

typedef enum {
    MM_MODEM_GSM_BAND_UNKNOWN      = 0x00000000,
    MM_MODEM_GSM_BAND_ANY          = 0x00000001,
    MM_MODEM_GSM_BAND_EGSM         = 0x00000002, /*  900 MHz */
    MM_MODEM_GSM_BAND_DCS          = 0x00000004, /* 1800 MHz */
    MM_MODEM_GSM_BAND_PCS          = 0x00000008, /* 1900 MHz */
    MM_MODEM_GSM_BAND_G850         = 0x00000010, /*  850 MHz */
    MM_MODEM_GSM_BAND_U2100        = 0x00000020, /* WCDMA 3GPP UMTS 2100 MHz     (Class I) */
    MM_MODEM_GSM_BAND_U1800        = 0x00000040, /* WCDMA 3GPP UMTS 1800 MHz     (Class III) */
    MM_MODEM_GSM_BAND_U17IV        = 0x00000080, /* WCDMA 3GPP AWS 1700/2100 MHz (Class IV) */
    MM_MODEM_GSM_BAND_U800         = 0x00000100, /* WCDMA 3GPP UMTS 800 MHz      (Class VI) */
    MM_MODEM_GSM_BAND_U850         = 0x00000200, /* WCDMA 3GPP UMTS 850 MHz      (Class V) */
    MM_MODEM_GSM_BAND_U900         = 0x00000400, /* WCDMA 3GPP UMTS 900 MHz      (Class VIII) */
    MM_MODEM_GSM_BAND_U17IX        = 0x00000800, /* WCDMA 3GPP UMTS 1700 MHz     (Class IX) */
    MM_MODEM_GSM_BAND_U1900        = 0x00001000, /* WCDMA 3GPP UMTS 1900 MHz     (Class II) */

    MM_MODEM_GSM_BAND_LAST = MM_MODEM_GSM_BAND_U1900
} MMModemGsmBand;


typedef enum {
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_ANY = 0,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_GPRS,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_EDGE,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_UMTS,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_HSDPA,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_2G_PREFERRED,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_3G_PREFERRED,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_2G_ONLY,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_3G_ONLY,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_HSUPA,
    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_HSPA,

    MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_LAST = MM_MODEM_GSM_NETWORK_DEPRECATED_MODE_HSPA
} MMModemDeprecatedMode;

#endif  /* MM_MODEM_GSM_H */
