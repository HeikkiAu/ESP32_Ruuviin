#ifndef __RUUVI_TAG_H__
#define __RUUVI_TAG_H__

#define  MAX_NBR_RUUVI_TAG  10  // tähän tagimäärä skannauksessa
#define  RUUVI_LOCATION_LEN 18
#define  NOT_A_RUUVI        255

#define  TARKISTA           true       // ruuvin muunnetut tulokset

typedef struct
{
  /* https://github.com/ruuvi/ruuvi-sensor-protocols/blob/master/dataformat_05.md */
  
    String    mac_addr;                       // FORMAT 5
    char      location[RUUVI_LOCATION_LEN];
    float     temp_fp;
    int16_t   temperature;                    // 1-2 // 6..10 // int16    // -32767... + 32767 // 0.005 astetta
    float     humidity;          // float     // 3-4 // 10..13 // uint16_t // 0...40000         // * 0.0025 %   
    int16_t   pressure;                       // 5-6 //  13..17// uint16_t   //  1Pa              // -50000 
    int16_t   acc[3];                         // 7-12 // 17 21 // int16_t   //int // ax x // ax y // ax z // akselit liike
    uint16_t  voltage_power;                  // 13-14 // 21..25 // uint 16 // 11bit + 5bit unsin 
    //                                                     // ensin 11 bit 1.6V+ (1.6V to 3.646V)in mV 
    //                                                     // 5 ubit on TX PWR yli -40dB in 2db steps
    float     voltage;                        // laskettu
    uint16_t  power;                          // laskettu
    int16_t   rssi;                           //    25-26 ??? jodstain otettava lukema laitteesta ?
    int16_t  movement;                       // 15       //26 37   uint8_t laskettuna xyz (0...254 )
    // int8_t    movement;                    // 15//   uint16  liikekeskeytys arvo voi olla sama
    uint16_t  measurement;                    //  16-17 // 27..31 // # of msmnt 
    // valid mac address                      //18-23 // 31...
    bool      updated;                        //  ?
} ruuvi_tag_st;


class RuuviTag
{
    public:    
        RuuviTag(void);
        int8_t  add(const char *addr, const char *loc);
        String  *get_addr(uint8_t indx);
        uint8_t get_index(String mac_addr);
        int8_t  add_if_new(const char *mac_address, const char *loc);
        ruuvi_tag_st *get_data_ptr(String mac_addr);

        bool    is_a_defined_ruuvi(String mac_addr);
        float   get_temperature(uint8_t indx);
        float   get_pressure(uint8_t indx);
        float   get_humidity(uint8_t indx);
        
                float   get_voltage(uint8_t indx );
                float   get_power(uint8_t indx ); 

        
        // uint16_t 
        float get_rssi(uint8_t indx);
        char    *get_location(uint8_t indx);
        
        bool     get_updated(uint8_t indx);
        void     clr_updated(uint8_t indx);
        void     decode_raw_data(String mac_addr, String raw_data, int rssi);
        //bool is_updated(uint8_t indx);
        //void clear_update(uint8_t indx);
        ruuvi_tag_st  ruuvi[MAX_NBR_RUUVI_TAG];
        uint8_t   nbr_of = 0;
   private:
        int8_t    _active_indx = 0;
        String    undef_addr = "xxx";
};


//void ruuvi_tag_initialize(void);

#endif
