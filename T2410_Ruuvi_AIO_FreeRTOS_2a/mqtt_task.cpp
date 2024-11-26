#include <WiFi.h>
#include "main.h"
#include "mqtt_task.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "ruuvi_tag.h"
#include "secrets.h"


extern main_ctrl_st main_ctrl;
extern WiFiClient client;
extern RuuviTag ruuvi_tag;
// Store the MQTT server, username, and password in flash memory.
// This is required for using the Adafruit MQTT library.
// xxx
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;


//infrapale/feeds/home-tampere.tampere-indoor-temperature
// ---------------------------------------------------------------
// Adafruit_MQTT_Subscribe *aio_subs[AIO_SUBS_NBR_OF] =
// {
//   [AIO_SUBS_TIME]           = &timefeed,
//   [AIO_SUBS_TRE_ID_TEMP]    = &tre_id_temp_feed,
//   [AIO_SUBS_TRE_ID_HUM]     = &tre_id_hum_feed,
//   [AIO_SUBS_LA_ID_TEMP]     = &lilla_astrid_id_temp,
//   [AIO_SUBS_VA_OD_TEMP]     = &villa_astrid_od_temp,
//   [AIO_SUBS_VA_OD_HUM]      = &villa_astrid_od_hum,
//   [AIO_SUBS_RUUVI_E6_TEMP]  = &ruuvi_e6_temp,
//   [AIO_SUBS_RUUVI_EA_TEMP]  = &ruuvi_ea_temp,
//   [AIO_SUBS_RUUVI_ED_TEMP]  = &ruuvi_ed_temp,
// };


Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);

// --------TILAP TOM----------------------------------------------------------
Adafruit_MQTT_Publish ruuvi_od_temp           = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/ulko-od-temp");
Adafruit_MQTT_Publish ruuvi_od_hum            = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/ulko-od-hum");
Adafruit_MQTT_Publish ruuvi_od_rssi           = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/ulko-od-rssi");
Adafruit_MQTT_Publish ruuvi_od_press          = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/ulko-od-press");

Adafruit_MQTT_Publish ruuvi_e3_temp           = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/patteri-temp");

Adafruit_MQTT_Publish ruuvi_e2_bat            = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/pakastin-bat");
Adafruit_MQTT_Publish ruuvi_e2_temp           = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/pakastin-temp");


// Adafruit_MQTT_Publish ruuvi_e2_hum            = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/portimo.pakastin-hum");
// Adafruit_MQTT_Publish ruuvi_e2_bat            = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/portimo.pakastin-bat");
// Adafruit_MQTT_Publish ruuvi_e2_rssi            = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/portimo.pakastin-rssi");


//Adafruit_MQTT_Publish ruuvi_e3_hum            = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/portimo.ruuvi-e3-hum");

//  Adafruit_MQTT_Publish ruuvi_e4_hum           = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/portimo.ruuvi-e4-hum");
// Adafruit_MQTT_Publish ruuvi_e5_rssi            = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/outo-patt-rssi");
// Adafruit_MQTT_Subscribe timefeed               = Adafruit_MQTT_Subscribe(&aio_mqtt, "time/seconds");


//---------TOM-----------------------------------------------------------------------

// Adafruit_MQTT_Publish por_id_temp_feed  = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/home-portimo.portimo-indoor-temperature");
// Adafruit_MQTT_Publish ruuvi_ea_temp  = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/portimo.ruuvi428c-od-temp");
// Adafruit_MQTT_Publish ruuvi_ea_rssi  = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/portimo.ruuvi428c-od-rssi");
// Adafruit_MQTT_Publish ruuvi_ea_bat   = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/Anttila.ruuvi0719-batt");
// Adafruit_MQTT_Publish ruuvi_ed_temp  = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/Anttila.ruuvi0719-temp");

ruuvi_publ_st ruuvi_publ[AIO_PUBL_NBR_OF ] =
{
    //  PORTIMOPOLKU, ULKO, PAKASTIN, PATTERI JA KUMMAsta RSSI  = 8 kpl
    { &ruuvi_od_temp, "f7:b7:f9:e1:42:8c", "PP-ulko-Temp",   NULL, false, UNIT_TEMPERATURE, 60000,  0}, 
    { &ruuvi_od_hum,  "f7:b7:f9:e1:42:8c", "PP-ulko-Hum",    NULL, false, UNIT_HUMIDITY   , 60000,  0}, 
    { &ruuvi_od_rssi, "f7:b7:f9:e1:42:8c", "PP-ulko-RSSI ",   NULL, false, UNIT_RSSI,        60000,  0},
    { &ruuvi_od_press,"f7:b7:f9:e1:42:8c", "PP-ulko-press",  NULL, false, UNIT_AIR_PRESSURE, 60000,  0},

     { &ruuvi_e3_temp, "eb:6c:a9:0b:41:f8", "PP-patt-Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0},
                          // EB:6C:A9:0B:41:F8

    { &ruuvi_e2_temp, "e3:f5:88:11:07:19", "PP-pakk-Temp",   NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
    { &ruuvi_e2_bat,  "e3:f5:88:11:07:19", "PP-pakk-Batt",   NULL, false, UNIT_VOLTAGE,     60000,   0},
   

  //  { &ruuvi_e2_temp, "e3:f5:88:11:07:19", "PP-pak-0719_Temp ", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
  //  { &ruuvi_e2_hum,  "e3:f5:88:11:07:19", "PP-pak-0719_Hum  ", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
  //   {&ruuvi_e2_rssi, "e3:f5:88:11:07:19", "Outo-RSSI-pak  ", NULL, false, UNIT_RSSI,        60000,  0},
   
    
    //{ &ruuvi_e3_hum,  "eb:6c:a9:0B:41:f8", "PP_patt_41f8-Hum  ", NULL, false, UNIT_HUMIDITY   , 60000,   0},   

    //{ &ruuvi_e5_rssi, "ea:78:e2:12:36:f8", "Outo-e5-rssi", NULL, false, UNIT_RSSI,        60000,  0}
    //    { &ruuvi_e4_hum,  "eb:6c:a9:0B:36:f8", "Outo Hum     ", NULL, false, UNIT_HUMIDITY   , 60000,   0},
  
};
 

/*
ruuvi_publ_st ruuvi_publ[AIO_PUBL_NBR_OF ] =  8 + 2 kppl
{
   //   Myrskyla ULKO, PANNU, KEITTIO, YLAKERTA, PYSTYPAK, NK_PAK, NK_TEMP NK_PAK_RSSI JOKIN BAT
    { &ruuvi_e11_temp, "eb:6c:a9:0B:41:f8", "My_od ulko  Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
    { &ruuvi_e12_temp, "eb:6c:a9:0B:41:f8", "My_id pannu Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
    { &ruuvi_e13_temp, "eb:6c:a9:0B:41:f8", "My_id keit  Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 

    { &ruuvi_e14_temp, "eb:6c:a9:0B:41:f8", "My_id_yk    Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
    { &ruuvi_e15_temp, "f7:b7:f9:e1:42:8c", "My id_pak   Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
    { &ruuvi_e15_rssi, "f7:b7:f9:e1:42:8c", "My id_pak   RSSI", NULL, false, UNIT_RSSI,        300000,  0}, 
    
    { &ruuvi_e16_temp, "ea:78:e2:12:36:f8", "My_NK_pak   Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
    { &ruuvi_e17_temp, "f7:b7:f9:e1:42:8c", "My_NK       Temp", NULL, false, UNIT_TEMPERATURE, 60000,   0}, 
    // { &ruuvi_e17_hum , "ea:78:e2:12:36:f8", "My_NK       Hum ", NULL, false, UNIT_HUMIDITY   , 60000,   0}, 
    // { &ruuvi_e17_rssi, "f7:b7:f9:e1:42:8c", "My_NK       RSSI", NULL, false, UNIT_RSSI,        300000,  0}, 
};
*/



void task_connect_mqtt( void *pvParameters )
{
    uint8_t       state;
    int8_t        ret;
    uint8_t       sensor_indx = 0;
    ruuvi_tag_st  *rptr;
    float         fval;
    
    state = 0;
    for (uint8_t pindx = 0; pindx < AIO_PUBL_NBR_OF; pindx++)
    {
       ruuvi_tag.add_if_new(ruuvi_publ[pindx].mac, ruuvi_publ[pindx].caption);
    }
    
    for (uint8_t pindx = 0; pindx < AIO_PUBL_NBR_OF; pindx++)
    {
        ruuvi_publ[pindx].ruuvi_ptr = ruuvi_tag.get_data_ptr(String (ruuvi_publ[pindx].mac));
        Serial.printf ("NYT ON JO PINdX  %d  of  %d  \n\n", pindx, AIO_PUBL_NBR_OF );
    }

    
    for (;;)
    { 
        printf("MQTT state: %d\n", state);
        switch(state) {
            case 0: // initial
                sensor_indx  = 0;
                state++;
                break;
            case 1: //Re-run MQTT action
                state++;
                break;
                
            case 2: // waiting for WiFi
                if (main_ctrl.wifi_is_connected && main_ctrl.radio_is_available)
                {
                    main_ctrl.radio_is_available = false;
                    state = 10;
                    digitalWrite(PIN_LED_YELLOW, HIGH);
                }                  
                vTaskDelay(1000);
                break;


            case 10:
                if (mqtt.connected())
                {
                    printf("MQTT was already connected\n");
                    main_ctrl.radio_is_available = false;
                    state = 20;
                }
                else 
                {
                    ret = mqtt.connect();              
                    if (ret != 0) {    // connect will return 0 for connected
                        printf("%s\nRetrying MQTT connection…\n",mqtt.connectErrorString(ret));
                        mqtt.disconnect();
                        main_ctrl.radio_is_available = true;
                        digitalWrite(PIN_LED_YELLOW, LOW);
                        state = 2;
                    }
                    else
                    {
                        main_ctrl.radio_is_available = false;
                        state = 20;
                    }
                }
                vTaskDelay(100);
                break;    
            case 20:  // MQTT is connected
                if (millis() >ruuvi_publ[sensor_indx].publ_next_ms)
                {
                    ruuvi_publ[sensor_indx].publ_next_ms = millis() + ruuvi_publ[sensor_indx].publ_interval_ms;
                    rptr = ruuvi_publ[sensor_indx].ruuvi_ptr;
                    switch(ruuvi_publ[sensor_indx].unit_type)
                    {
                        case UNIT_TEMPERATURE:
                            fval =  rptr->temp_fp; 
                            break;
                        case UNIT_HUMIDITY:
                            fval = rptr->humidity;
                            break;
                        case UNIT_AIR_PRESSURE:
                            fval = rptr->pressure;
                            break;
                        case UNIT_LIGHT:
                            fval = 0.0;
                            break;
                        case UNIT_LDR:
                            fval = 0.0;
                            break;
                        case UNIT_RSSI:
                            fval = (float)rptr->rssi;
                            break;
                        case UNIT_VOLTAGE:
                            fval = rptr->voltage;
                            break;


                    }
                    printf("MQTT Publish: %s %f\n", ruuvi_publ[sensor_indx].caption,  fval);
                    ruuvi_publ[sensor_indx].ada_mqtt_publ->publish(fval);      
                    vTaskDelay(5000);
                }
                else
                {
                    vTaskDelay(1000);
                }
                if(++sensor_indx >=  AIO_PUBL_NBR_OF) sensor_indx = 0;         
                state = 30;
                break;    
            case 30:
                mqtt.disconnect(); 
                main_ctrl.radio_is_available = true;
                digitalWrite(PIN_LED_YELLOW, LOW);
                vTaskDelay(1000);
                state = 2;
                break;    

            default:
                printf("Fatal error: incorrect MQTT state -> WDT reset…%d\n",state);
                vTaskDelay(100);
                state = 1;
                break;           
        }
      //vTaskDelay(100);
    }
}

