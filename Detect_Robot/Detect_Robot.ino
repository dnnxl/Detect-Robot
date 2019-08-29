#include <Servo.h>            // Incluir la biblioteca del Servo.
Servo servo;                  // Definir una instancia de servo.

// Modulo joystick
int angulo = 0 ;                // Inicializar el valor del angulo a 0 grados.
int Eje_X = A1 ;                // Inicializar la variable Eje_X al pin analogico A1.
int Eje_Y = A2 ;                // Inicializar la variable Eje_y al pin analogico A2.
int boton = 1;                  // Inicializar la variable boton al pin digital 1.

// Modulo Servo
int ServoPin = 0;               // Inicializar la variable ServoPin al pin digital 0.

// Modulo sensor ultrasonido
const int trigPin = 2;          // Constante entero al pin digital 2
const int echoPin = 3;          // Constante entero al pin digital 3

// Definir otras variables
long duration;                  // Variable que almacena la duración del echo del sensor ultrasonido.
int distance;                   // Variable que almacena la distancia que se encuentra el objeto detectado.

// Modulo buzzer
int Buzzer = 4;                 // Inicializar la variable Buzzer al pin digital

void setup()                    // Función setup, solo se ejecuta una vez en todo el programa.
{
  servo.attach(ServoPin) ;      // Unir el pin 0 del ServoPin a la instancia del servo.
  pinMode(boton, INPUT_PULLUP); // Definir el pin boton como entrada.
  pinMode(trigPin, OUTPUT);     // Define el pin trigPin como salida.
  pinMode(Buzzer, OUTPUT);      // Define el pin del buzzer como salida.
  pinMode(echoPin, INPUT);      // Define el pin de echoPin como entrada.
}

void loop()                     // Funcion loop, es un bucle, se repite
{
  angulo = map(analogRead(A1), 0, 1024, 0, 180); // Mapea valores obtenidos del servo de 0 a 1024 a 0 hasta 180 para obtener el angulo.
  servo.write(angulo);                        // Mueve el servo al angulo mapeado anteriormente.
  delay(250);                                 // Atrasa 250 milisegundos.

  digitalWrite(trigPin, LOW);                 // Desactiva el pin trigPin.
  delayMicroseconds(2);                       // Atrasa 2 microsegundos.
  digitalWrite(trigPin, HIGH);                // Activa el trigPin a alto
  delayMicroseconds(10);                      // Atrasa 10 segundos.
  digitalWrite(trigPin, LOW);                 // Desactiva el pin trigPin.

  duration = pulseIn(echoPin, HIGH);          // Lee el echoPin, devuelve el tiempo de viaje de la onda de sonido en microsegundos
  distance = (duration / 2) / 29.1;           // Calcular la distancia
  if (distance >= 200 || distance <= 0)       // Si la distancia es mayor a 200 o menor a 0 no se detecta ningún objeto.
  {
    Serial.println("no object detected");
    Serial.println(distance);

    digitalWrite(Buzzer, LOW);                // Desactiva el buzzer
    noTone(Buzzer);                          // Pone en frecuencia de 0Hz al buzzer
    delay(1200);
  }
  else
  {
    Serial.println("object detected \n");
    tone(Buzzer, 5);                        // Pone en frecuencia en 200Hz
    delay(500);
    noTone(Buzzer);
  }
}
