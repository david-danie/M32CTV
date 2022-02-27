# M32CTV

<div align="justify">Aquí hay código para automatizar el encendido/apagado de algunos dispositivos usados en invernaderos. Se usa un microcontrolador de 8 bits cargado con el bootloader de Arduino, comunicación inalámbrica via UART, temporización con un RTC y algo de electrónica para activar los relevadores para una bomba de riego, ventiladores y/o extractores, y lámparas de cutivo. <b>Este repo se está construyendo.</b></div>
<br>
<div align="center"><img src="./src/R9-46W.png" alt="imagen" width="675" height="345"/><br></div>

## 1. DESCRIPCIÓN DE LOS COMPONENTES
<div align="justify">Los invernaderos ofrecen muchas ventajas sobre los métodos de agricultura tradicionales. En la ciudad el cultivo de algunas plantas y hortalizas es más común actualmente y la tecnología usada en la agricultura protegida también se puede adaptar a espacios dedicados en la ciudad. Esta tecnología puede incluir la automatización de tareas como el riego, ventilación/extracción, luz (fotoperiodo) y medición de parámetros como temperatua, humedad, PH, etc.
</div>
<br>

<div>
<ul>
 <li align="justify"><b>Luz.</b><br>El sol es una gran fuente de energía e influye directamente en el desarrollo de los seres vivos. Hoy existen lámparas de cultivo que emulan la radiación solar, algunas usan los colores rojo y azul principalmente. Se dispone de <b>1 pin digital</b> del microcontrolador para el control de una lámpara en CA.</li><br>
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
 <li align="justify"><b>Riego.</b><br>Existen diferentes sistemas de riego, se pueden mencionar algunos como: asperción, goteo, por gravedad, nft, entre otros. Se hace uso de una bomba de agua o de una electroválvula para activar el flujo de agua en el cultivo. <b>Se dispone de 1 pin digital para esta tarea.</b></li><br>
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
<li align="justify"><b>Ventilación/extracción.</b><br>La calidad del aire influye en el crecimiento de las plantas y en la temperatura de los invernaderos. Algunas veces es necesario forzar la cirulación aire limpio en los invernaderos y eliminar el aire viciado. <b>Se dispone de 1 pin digital del microcontrolador</b> para el control de un ventilador y/o extractor en CA.</li>
</ul>
</div>

## 2. TARJETA DE CONTROL
<div align="justify">Aquí se documentará sobre la tarjeta de control propuesta.</div><br>
<ul>
<li>Salidas digitales.</li>
<li>Real Time Clock.</li>
<li>Comunicación inalámbrica.</li>
</ul>

## 3. INSTALACIÓN ELÉCTRICA
<div align="justify">Aquí se documentará sobre la instalación eléctrica propuesta.</div><br>

<ul>
<li>Contactores.</li>
<li>Interruptores Termomagnéticos.</li>
<li>Diagrama Eléctrico.</li>
</ul>
