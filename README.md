# -SPACE
**Τίτλος: Αυτοματοποιημένο σύστημα εντοπισμού και ειδοποίησης για δασικές πυρκαγιές**

Ομάδα: S.P.A.C.E.

Περιγραφή: Με machine learning εκπαιδεύσαμε ένα raspberry Pi να διαχωρίζει φωτογραφίες που παίρνονται σε πραγματικό χρόνο από ένα παρατηρητήριο και να αναγνωρίζει καπνό ή φωτιά. Σε περίπτωση που αναγνωριστεί καπνός ή φωτιά, το raspberry Pi στέλνει μήνυμα κινδύνου μέσω ενός Feather M0 Lora από το παρατηρητήριο, στο αντίστοιχο Feather M0 Lora στο σταθμό Βάσης που συλλέγει τις πληροφορίες. Η επικοινωνία των Feather είναι ασύρματη μέσω FM. Ο σταθμός Βάσης λειτουργεί ως αυτοματοποιημένο κέντρο ειδοποίησης. Ο δεύτερος μικρο-επεξεργαστής Feather, ανάβει στο κέντρο ειδοποίησης ένα από τρία χρωματιστά leds ανάλογα με την πληροφορία που έλαβε: Λίγος καπνός, Πολύς καπνός, Φωτιά. Επίσης το Adafruit Feather M0 LoRa θα μετράει τη θερμοκρασία την ατμοσφαιρική πίεση και την υγρασία με κατάλληλους αισθητήρες καθιστώντας το ένα μικρό μετεωρολογικό σταθμό.

Εκπαιδευτικοί στόχοι:
1. Εξειδίκευση στο Machine Learning
2. Προγραμματισμός Arduino/Raspberry Pi
3. Συνδεσμολογία αισθητήρων και επεξεργαστών
4. 3D σχεδίαση
5. Ευαισθητοποίηση σε περιβαλλοντικά θέματα
6. Ανάπτυξη ομαδικότητας
7. Ανάπτυξη κριτικής σκέψης για επίτευξη στόχων

Λίστα προτεινόμενου εξοπλισμού:
1.   Ένα Raspberry Pi 4 Model B Kit (8GB),  129 ευρώ.  
https://www.hellasdigital.gr/go-create/raspberry-and-accessories-el/raspberry-pi-4-and-accessories/raspberry-pi-4-model-b-8gb-low-budget-kit-pi4lb8gb/

https://www.raspberrypi.com/products/raspberry-pi-4-model-b/

2.  Δύο Adafruit Feather M0 LoRa, 0 ευρώ.
https://www.adafruit.com/product/3179

3. 4 χρώματα λαμπτήρων, κόκκινο, μπλε, κίτρινο, πράσινο,  1.5 ευρώ.     
https://www.hellasdigital.gr/electronics/optoelectronics/10pcs-f3-5mm-red-color-red-light-round-superbright-led/

5. Ένα BME280,   https://www.hellasdigital.gr/electronics/sensors/bme280-environmental-sensor-temperature-humidity-barometric-pressure/ ,   16 ευρώ.
https://grobotronics.com/adafruit-bme280-i2c-or-spi-temperature-humidity-pressure-sensor.html

6. Ένα breadboard  https://www.hellasdigital.gr/electronics/prototyping/pcb-breadboard/breadboard-translucent-self-adhesive-clear-prt-09567/  ,    5 ευρώ.
7. Δύο buzzer, https://www.hellasdigital.gr/electronics/components/buzzer/passive-buzzer-alarm-sensor-module/ ,   1 ευρώ.

