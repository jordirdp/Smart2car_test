# Smart2car_test
🔗Creado por [Jordi Rodriguez](https://github.com/jordirdp)  

👨🏻‍💻Práctica de **programación visual con bloques** en Arduino  
    
### Software  
- Programado con [ArduinoBlocks](http://www.arduinoblocks.com/web/)  
- Este código simplemente realiza un test del hardware instalado


### Hardware  
- Arduino UNO  
- Arduino Shield Sensor v.5.0
- HC-SR04 = Sensor ultrasonido de distancia
- TCRT5000 = Sensor infrarrojo de proximidad (2x)
- LM393 = Sensor fotolumínico
- LCD I2C = Pantalla lcd
- Led blanco + R100Ω (2x)
- Led rojo + R220Ω (2x)
- Buzzer activo + R100Ω  
- L298N = Controlador de motores
- Motores Arduino (2x)

### Montaje  
![Imagen Smart2car acabado](Smart2car_final.jpeg)  
Conexiones a pines Arduino UNO:  

    - A00 = Sensor ultrasonido-Echo (HC-SR04)  
    - A01 = Sensor ultrasonido-Trigger (HC-SR04)  
    - A02 = Sensor línea izquierda (TCRT5000)  
    - A03 = Fotosensor (LM393)  
    - A04 = I2C LCD (SDA)  
    - A05 = I2C LCD (SCL)  

    - D00 = (RX)
    - D01 = (TX)  
    - D02 = Led blanco derecho  
    - D03-= Led rojo derecho  
    - D04 = Sensor línea derecha   
    - D05-= ENB motor izquierdo  
    - D06-= ENA motor derecho  
    - D07 = IN1 motor derecho  
    - D08 = IN2 motor derecho  
    - D09-= IN3 motor izquierdo  
    - D10-= IN4 motor izquierdo  
    - D11-= Buzzer  
    - D12 = Led rojo izquierdo   
    - D13 = Led blanco izquierdo  

### Licencia  
⚖️Todo el contenido distribuido bajo [licencia GPL-3.0](https://www.gnu.org/licenses/gpl-3.0), salvo indicación expresa.  
Las referencias y librerías empleadas, estarán sujetas a sus propia licencia, y no se incluyen en este repositorio.  
