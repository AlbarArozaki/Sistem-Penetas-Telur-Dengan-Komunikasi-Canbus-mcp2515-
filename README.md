# Sistem-Penetas-Telur-Dengan-Komunikasi-Canbus-(mcp2515)

![prototype](https://github.com/AlbarArozaki/Sistem-Penetas-Telur-Dengan-Komunikasi-Canbus-mcp2515-/blob/main/Prototype.jpg)


<p style="text-align: justify"> Sistem penetas telur dengan mikrokontroler Arduino UNO dan esp32 serta menggunakan canbus(mcp2515) untuk komunikasi data dengan user interface Blynk. <br /> Menggunakan sensor dht22 untuk mengukur suhu dan relay sebagai pengontrol nyala lampu pijar, data suhu ditampilkan di Blynk </p>

![tampilan blynk](https://github.com/AlbarArozaki/Sistem-Penetas-Telur-Dengan-Komunikasi-Canbus-mcp2515-/blob/main/Tampilan%20Blynk.jpg)

<p style="text-align: justify"> Arduino UNO bertindak sebagai transceiver dan esp32 sebagai receiver dan terdapat LCD I2C pada Arduino UNO. <br /> Sensor dht22 dan relay terhubung di Arduino UNO, kemudian data dari sensor dht22 dikirim oleh Arduino UNO <br /> melalui modul canbus (mcp2515) ke esp32 dan ditampilkan di Blynk </p>
