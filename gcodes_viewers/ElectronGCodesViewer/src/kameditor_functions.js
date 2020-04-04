function handleFileSelect(evt) {
  var files = evt.target.files; // FileList object
  //alert(evt.target);

  FileIO.load(files[0], function(gcode) {
      GCodeImporter.importText(gcode, onGCodeLoaded);
    });
}

function readTextFile(path)
{
  //alert("load: " + path)
  var rawFile = new XMLHttpRequest();
  rawFile.open("GET", path, false);
  rawFile.onreadystatechange = function ()
  {
      if(rawFile.readyState === 4)
      {
          if(rawFile.status === 200 || rawFile.status == 0)
          {
              var allText = rawFile.responseText;
              GCodeImporter.importText(allText, onGCodeLoaded);
          }
      }
  }
  rawFile.send(null);
}