# Indicador de aparcamiento

Este código está diseñado para controlar un indicador de aparcamiento que utiliza un sensor de ultrasonidos para medir la distancia a un objeto y mostrar mediante dos LED si un estacionamiento está libre o ocupado.
Definición de pines

El primer bloque de código define los pines que se van a utilizar para conectar el sensor de ultrasonidos y los dos LED. Se utilizan los pines digitales 2 y 3 para el Trigger y Echo del sensor respectivamente, y los pines digitales 8 y 9 para los LED rojo y verde.

```c
// Definición de los pines que se van a utilizar
const int Trigger = 2;   // Pin digital 2 para el Trigger del sensor
const int Echo = 3;      // Pin digital 3 para el Echo del sensor
int ledR = 8;            // Pin digital 8 para el LED rojo
int ledV = 9;            // Pin digital 9 para el LED verde

```

## Configuración de los pines

El siguiente bloque de código se encarga de configurar los pines previamente definidos como entrada o salida según corresponda. También se inicializa el pin del Trigger con un valor bajo.

```c
void setup() {
  // Inicialización de la comunicación serial
  Serial.begin(9600);
  // Configuración de los pines como entrada o salida
  pinMode(Trigger, OUTPUT);   // El pin del Trigger se configura como salida
  pinMode(Echo, INPUT);       // El pin del Echo se configura como entrada
  pinMode(ledR, OUTPUT);      // El pin del LED rojo se configura como salida
  pinMode(ledV, OUTPUT);      // El pin del LED verde se configura como salida
  // Inicialización del pin del Trigger con un valor bajo
  digitalWrite(Trigger, LOW);
}
```

## Medición de la distancia

El bloque de código siguiente se encarga de medir la distancia utilizando el sensor de ultrasonidos. Primero se envía un pulso de 10 microsegundos al pin del Trigger y se espera la llegada del eco al pin del Echo. A continuación, se calcula la distancia en centímetros a partir del tiempo que tarda el eco en llegar.

```C
void loop() {
  // Declaración de variables
  long t;  // Tiempo que tarda en llegar el eco
  long d;  // Distancia en centímetros
  
  // Envío de un pulso de 10us al pin del Trigger
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  
  // Lectura del tiempo que tarda en llegar el eco
  t = pulseIn(Echo, HIGH);
  // Escalado del tiempo a una distancia en centímetros
  d = t/59;
```

## Comprobación de la distancia

El siguiente bloque de código compara la distancia medida con un valor umbral de 12 centímetros. Si la distancia es menor o igual a 12 centímetros, se asume que hay un objeto cerca y se enciende el LED rojo mientras se apaga el LED verde para indicar que el estacionamiento está ocupado. Si la distancia es mayor a 12 centímetros, se enciende el LED verde y se apaga el LED rojo para indicar que el estacionamiento está libre.

```c
 // Comprobación de la distancia medida
  if (d <= 12) {  // Si la distancia es menor o igual a 12cm
    Serial.println("Aparcao");  // Envío de un mensaje por comunicación serial
    digitalWrite(ledR, HIGH);  // Apagado del LED verde
    digitalWrite(ledV, LOW);   // Encendido del LED rojo
  } else {        // Si la distancia es mayor a 12cm
    Serial.println("Libre");    // Envío de un mensaje por comunicación serial
    digitalWrite(ledR, LOW);   // Encendido del LED verde
    digitalWrite(ledV, HIGH);  // Apagado del LED rojo
  }
  
  // Pausa de 100ms antes de la siguiente lectura
  delay(100);
}
```
Después de la comprobación de la distancia, el código establece el estado de los LED en función de la distancia medida. Si la distancia es menor o igual a 12 centímetros, se establece el LED rojo en estado alto y el LED verde en estado bajo, indicando que el espacio de estacionamiento está ocupado. En cambio, si la distancia es mayor a 12 centímetros, se establece el LED rojo en estado bajo y el LED verde en estado alto, lo que indica que el espacio de estacionamiento está libre.

Por último, el código agrega una pausa de 100 milisegundos antes de comenzar la siguiente lectura del sensor. Este retraso es necesario para permitir que los pulsos ultrasónicos emitidos por el sensor se disipen antes de realizar una nueva lectura.
