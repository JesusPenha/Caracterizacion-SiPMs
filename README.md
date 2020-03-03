Este repositorio contiene los archivos y los codigos utilizados para la caracterización de los fotomultiplicadores de silicio S133601350CS de hamamatsu.

-La carpeta FotonEquivalente contiene los codigos para el cálculo del equivalente en voltaje de un fotón (p.e) y una gráfica de la función de densidad de probabilidad (PDF) para un conjunto de 10.000 eventos.

contiene los datos de la corrtiente oscura y voltaje de polarización para el SiPM a diferentes temperaturas.

-La carpeta LEDPulser contiene la descripcion de Hardware en VHDL para la FPGA utilizada para el módulo de generación de pulsos realizado en ISE design suite- Xilinx.

-El script After_Cross_1350CS.ipynb permite realizar el analisis de ruido correlacionado (crosstalk y afterpulses).

-El script BreakdownV.ipynb permite obtener la relación entre el voltaje de ruptura y la temperatura a partir de los archivos almacenados en la cerpeta 1350CS.

-El script Data_Record.py es el utilizado por el DAQ (Red pitaya) para el registro y almacenamieto de los eventos (pulsos) en el SiPM.

-El script Noise.ipynb permite obtener los histogramas de carga y de pico necesarios para la caracterización del ruido.

-El script PID_control.ino contiene el algoritmo de control del controlador PID utilizado en el sistema de control de temperatura.
