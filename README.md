# M32CTV

<div align="justify">Aquí hay código para automatizar el encendido/apagado de algunos dispositivos usados en invernaderos. Se usa un microcontrolador de 8 bits cargado con el bootloader de Arduino, comunicación inalámbrica via UART, temporización con un RTC y algo de electrónica para activar contactores de una bomba de riego, ventiladores y/o extractores, y lámparas de cutivo. <b>En ...</b></div>
<br>
<div align="center"><img src="./src/R9-46W.png" alt="imagen" width="675" height="345"/><br></div>

## 1. COMPONENTES
<div align="justify">Los invernaderos ofrecen muchas ventajas sobre los métodos de agricultura tradicionales. El cultivo de algunas plantas y hortalizas puede adaptarse a espacios dedicados en la ciudad. La tecnología usada en la agricultura protegida también se puede adaptar a estos lugares y  puede pensarse en; la automatización de tareas como el riego, ventilación/extracción, luz (fotoperiodo) y medición de parámetros como temperatua, humedad, PH, etc.
</div>
<br>

<div>
<ul>
 <li align="justify"><b>Luz.</b><br>El sol como fuente de energía es una muy potente e influye directamente en el desarrollo de vida. Dentro del espectro de radiación solar encontramos la radiación fotosintéticamente activa, donde los tonos azules y rojos son los más influyentes en el desarrollo de las plantas. La tecnología LED en la actualidad ofrece alternativas para suministro de luz en los cultivos. Se dispone de <b>1 pin digital</b> del microcontrolador para el control de una lámpara en CA.</li><br>
<table align="center">
  <tr>
    <th>Led rojo/azul.</th>
    <th>Led blanco.</th>
    <th>Otras lámparas.</th>
  </tr>
  <tr>
    <td align="center"><img src="./src/hyd_l.jpg" alt="imagen" width="100" height="100"/></td>
    <td align="center"><img src="./src/phi_lw.jpg" alt="imagen" width="100" height="100"/></td>
    <td align="center"><img src="./src/phi_so.jpg" alt="imagen" width="100" height="100"/></td>
  </tr>
</table>

  <li align="justify"><b>Riego.</b><br>Hay diferentes métodos de riego en la agricultura y se pueden mencionar algunos como: riego por asperción, por goteo, por gravedad, película de nutrientes, entre otros. Se hace la generalización de controlar el encendido/apagado de una bomba de agua o una electroválvula para realizar esta tarea.<b>Se dispone de 1 pin digital para el control.</b>  
  </li> 

 <br>

 <table align="center">
  <tr>
    <th>Goteo.</th>
    <th>Gravedad.</th>
    <th>Película de nutrientes.</th>
   <th>Válvula E.</th>
  </tr>
  <tr>
    <td align="center"><img src="./src/goteo.jpg" alt="imagen" width="100" height="100"/></td>
    <td align="center"><img src="./src/grav1.jpg" alt="imagen" width="100" height="100"/></td>
    <td align="center"><img src="./src/NFT.jpg" alt="imagen" width="100" height="100"/></td>
    <td align="center"><img src="./src/valve.jpg" alt="imagen" width="100" height="100"/></td>
  </tr>
</table>
  <li align="justify"><b>Ventilación/extracción.</b><br>La calidad del aire de los espacios de cultivo influye en la temperatura y por lo tanto en el desarrollo de las plantas. Si es necesario forzar la cirulación aire limpio en los invernaderos y eliminar el aire viciado se incluyen equipos de extracción, ventilación y algunas veces calefacción.<b>Se dispone de 1 pin digital del microcontrolador</b> para el control de un ventilador y/o extractor en CA.
  </li>
</ul>
</div>

## 2. TARJETA DE CONTROL
<div align="justify">El microcontrolador Atmega328 de Microchip/Atmel es un dispositivo de 8 bits con arquitectura RISC. Tiene 32 KB de memoria de programa, cuenta con hasta 23 pines que se pueden configurar como salidas o entradas y puede trabajar con un cristal externo de hasta 16 MHz para obtener hasta 16 MIPS. Tiene la capacidad de cargase con el bootloader de Arduino. Los periféricos que se ocupan en este proyeto son I2C, UART interface, salidas PWM y un bloque de salidas digitales para los actuadores.</div><br>
<ul>
<li><b>Salidas digitales.</b></li>
<br>
Se ocupan 3 salidas digitales para la activación de los componentes mencionados (lámpara, bomba de agua y ventilador/extractor). Estás salidas están conectadas a SSR's () los cuales nos permiten activar las bobinas en CA de los respectivos contactores.<br>
<li><b>Real Time Clock.</b></li>
<br>
Para temporizar el encendido y apagado que deben tener los equipos, se usa un RTC a través del puerto I2C. Nuestro dispositivo maestro, realizará lecturas del RTC en el bucle principal y dependiendo de las variables de apagado de cada dispositivo, se procederá a activar o desactivar los pines correspondientes.<br>
<li>Comunicación inalámbrica.</li><br>
La interface UART<br>
</ul>

## 3. INSTALACIÓN ELÉCTRICA
<div align="justify">Aquí se documentará sobre la instalación eléctrica propuesta.</div><br>

<ul>
<li>Contactores.</li>
<li>Interruptores Termomagnéticos.</li>
<li>Diagrama Eléctrico.</li>
</ul>
