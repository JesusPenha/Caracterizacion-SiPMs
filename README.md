Este repositorio contiene los archivos y los codigos utilizados para la caracterización de los fotomultiplicadores de silicio S133601350CS de hamamatsu.

-La carpeta FotonEquivalente contiene los codigos para el cálculo del equivalente en voltaje de un fotón (p.e) y una gráfica de la función de densidad de probabilidad (PDF) para un conjunto de 10.000 eventos.

-La carpeta Ganancia contiene los codigos para realizar la gráfica de la dependencia de la ganancia en función del sobre voltaje (OV) y de la temperatura (T), asi como los histogramas de carga respectivos.

-En la carpeta Modulos se encuentran los diseños de los circuitos impresos (Eagle) utilizados para cada módulo desarrollado así como los codigos (Arduino) relacionados con el control de temperatura y el medidor de corriente. Adicionalmente contiene la descripcion de Hardware en VHDL para la FPGA utilizada para el módulo de generación de pulsos realizado en ISE design suite- Xilinx.

-La carpeta Ruido están los codigos utilizados para obtener el ruido no correlacionado (DCR) y ruido  correlacionado (afterpulse y crosstalk). 

-La carpeta Voltaje_ruptura contiene los datos de la corrtiente oscura y voltaje de polarización para el SiPM a diferentes temperaturas y el script BreakdownV.ipynb permite obtener la relación entre el voltaje de ruptura y la temperatura a partir de los archivos almacenados en la cerpeta 1350CS.

-El script Data_Record.py es el utilizado por el DAQ (Red pitaya) para el registro y almacenamieto de los eventos (pulsos) en el SiPM.

-El archivo Registro_SiPM.xlsx contiene los registros de voltaje de operacion y corriente oscura a 25°C para 134 SiPMs S13360-1350CS de Hamamatsu.
