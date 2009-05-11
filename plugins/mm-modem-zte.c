/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mm-modem-zte.h"
#include "mm-serial.h"
#include "mm-errors.h"
#include "mm-callback-info.h"

static gpointer mm_modem_zte_parent_class = NULL;

MMModem *
mm_modem_zte_new (const char *data_device,
                  const char *driver)
{
    g_return_val_if_fail (data_device != NULL, NULL);
    g_return_val_if_fail (driver != NULL, NULL);

    return MM_MODEM (g_object_new (MM_TYPE_MODEM_ZTE,
                                   MM_SERIAL_DEVICE, data_device,
                                   MM_MODEM_DRIVER, driver,
                                   NULL));
}

/*****************************************************************************/
/*    Modem class override functions                                         */
/*****************************************************************************/

static void
init_modem_done (MMSerial *serial,
                 GString *response,
                 GError *error,
                 gpointer user_data)
{
    MMCallbackInfo *info = (MMCallbackInfo *) user_data;

    if (error)
        info->error = g_error_copy (error);

    mm_callback_info_schedule (info);
}

static void
pin_check_done (MMModem *modem, GError *error, gpointer user_data)
{
    MMCallbackInfo *info = (MMCallbackInfo *) user_data;

    if (error) {
        info->error = g_error_copy (error);
        mm_callback_info_schedule (info);
    } else
        /* Finish the initialization */
        mm_serial_queue_command (MM_SERIAL (modem), "Z E0 V1 X4 &C1 +CMEE=1;+CFUN=1;", 10, init_modem_done, info);
}

static void
pre_init_done (MMSerial *serial,
               GString *response,
               GError *error,
               gpointer user_data)
{
    MMCallbackInfo *info = (MMCallbackInfo *) user_data;

    if (error) {
        info->error = g_error_copy (error);
        mm_callback_info_schedule (info);
    } else {
        /* Now check the PIN explicitly, zte doesn't seem to report
           that it needs it otherwise */
        mm_generic_gsm_check_pin (MM_GENERIC_GSM (info->modem), pin_check_done, info);
    }
}

static void
enable_flash_done (MMSerial *serial, gpointer user_data)
{
    mm_serial_queue_command (serial, "E0 V1", 3, pre_init_done, user_data);
}

static void
disable_done (MMSerial *serial,
              GString *response,
              GError *error,
              gpointer user_data)
{
    mm_serial_close (serial);
    mm_callback_info_schedule ((MMCallbackInfo *) user_data);
}

static void
disable_flash_done (MMSerial *serial, gpointer user_data)
{
    mm_serial_queue_command (serial, "+CFUN=0", 5, disable_done, user_data);
}

static void
enable (MMModem *modem,
        gboolean do_enable,
        MMModemFn callback,
        gpointer user_data)
{
    MMCallbackInfo *info;

    /* First, reset the previously used CID */
    mm_generic_gsm_set_cid (MM_GENERIC_GSM (modem), 0);

    info = mm_callback_info_new (modem, callback, user_data);

    if (!do_enable) {
        if (mm_serial_is_connected (MM_SERIAL (modem)))
            mm_serial_flash (MM_SERIAL (modem), 1000, disable_flash_done, info);
        else
            disable_flash_done (MM_SERIAL (modem), info);
    } else {
        if (mm_serial_open (MM_SERIAL (modem), &info->error))
            mm_serial_flash (MM_SERIAL (modem), 100, enable_flash_done, info);

        if (info->error)
            mm_callback_info_schedule (info);
    }
}

/*****************************************************************************/

static void
modem_init (MMModem *modem_class)
{
    modem_class->enable = enable;
}

static void
mm_modem_zte_init (MMModemZte *self)
{
    GRegex *regex;

    mm_generic_gsm_set_unsolicited_registration (MM_GENERIC_GSM (self), TRUE);
    g_object_set (G_OBJECT (self), MM_SERIAL_CARRIER_DETECT, FALSE, NULL);

    regex = g_regex_new ("\\r\\n\\+ZUSIMR:(.*)\\r\\n", G_REGEX_RAW | G_REGEX_OPTIMIZE, 0, NULL);
    mm_serial_add_unsolicited_msg_handler (MM_SERIAL (self), regex, NULL, NULL, NULL);
    g_regex_unref (regex);

    regex = g_regex_new ("\\r\\n\\+ZDONR: (.*)\\r\\n", G_REGEX_RAW | G_REGEX_OPTIMIZE, 0, NULL);
    mm_serial_add_unsolicited_msg_handler (MM_SERIAL (self), regex, NULL, NULL, NULL);
    g_regex_unref (regex);

    regex = g_regex_new ("\\r\\n\\+ZPASR: (.*)\\r\\n", G_REGEX_RAW | G_REGEX_OPTIMIZE, 0, NULL);
    mm_serial_add_unsolicited_msg_handler (MM_SERIAL (self), regex, NULL, NULL, NULL);
    g_regex_unref (regex);

    regex = g_regex_new ("\\r\\n\\+ZEND\\r\\n", G_REGEX_RAW | G_REGEX_OPTIMIZE, 0, NULL);
    mm_serial_add_unsolicited_msg_handler (MM_SERIAL (self), regex, NULL, NULL, NULL);
    g_regex_unref (regex);
}

static void
mm_modem_zte_class_init (MMModemZteClass *klass)
{
    mm_modem_zte_parent_class = g_type_class_peek_parent (klass);
}

GType
mm_modem_zte_get_type (void)
{
    static GType modem_zte_type = 0;

    if (G_UNLIKELY (modem_zte_type == 0)) {
        static const GTypeInfo modem_zte_type_info = {
            sizeof (MMModemZteClass),
            (GBaseInitFunc) NULL,
            (GBaseFinalizeFunc) NULL,
            (GClassInitFunc) mm_modem_zte_class_init,
            (GClassFinalizeFunc) NULL,
            NULL,   /* class_data */
            sizeof (MMModemZte),
            0,      /* n_preallocs */
            (GInstanceInitFunc) mm_modem_zte_init,
        };

        static const GInterfaceInfo modem_iface_info = {
            (GInterfaceInitFunc) modem_init
        };

        modem_zte_type = g_type_register_static (MM_TYPE_GENERIC_GSM, "MMModemZte", &modem_zte_type_info, 0);
        g_type_add_interface_static (modem_zte_type, MM_TYPE_MODEM, &modem_iface_info);
    }

    return modem_zte_type;
}