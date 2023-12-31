//\\ Taha Al-jumaily //\\

#include <dht_nonblocking.h>
#include <LiquidCrystal.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

/*
 * Initialize the serial port.
 */
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup( ){
  Serial.begin( 9600);

  // Initialize LCD
  lcd.begin(16,2);
  }


/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity ){
  static unsigned long measurement_timestamp = millis( );
  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul ){
    if( dht_sensor.measure( temperature, humidity ) == true ){
      measurement_timestamp = millis( );
      return( true );
      }
    }
  return( false );
  }



/*
 * Main program loop.
 */
void loop( ){
  float temperature;
  float humidity;
  float Fahrenheit;
  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true ){
    Fahrenheit = (temperature * 1.8) + 32;
    Serial.print( "T = " );
    Serial.print(Fahrenheit, 1 );
    Serial.print( " deg. F, H = " );
    Serial.print(humidity, 1 );
    Serial.println( "%" );

    // Display humidity and temperature on the LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");

    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(Fahrenheit);
    lcd.print(" F");
  

    }
  }
