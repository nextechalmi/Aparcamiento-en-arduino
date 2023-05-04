// Definición de los pines que se van a utilizar
const int Trigger = 2;   // Pin digital 2 para el Trigger del sensor
const int Echo = 3;      // Pin digital 3 para el Echo del sensor
int ledR = 8;            // Pin digital 8 para el LED rojo
int ledV = 9;            // Pin digital 9 para el LED verde

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
  
  // Envío del valor de la distancia por comunicación serial
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.print("cm");
  Serial.println();
  
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
