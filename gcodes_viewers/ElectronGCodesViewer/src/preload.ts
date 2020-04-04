// All of the Node.js APIs are available in the preload process.
// It has the same sandbox as a Chrome extension.
import fs = require('fs');
import { ipcRenderer } from 'electron';

window.addEventListener("DOMContentLoaded", () => {
  let gcodesFilePath = ipcRenderer.sendSync("getGCodesFilePath");

  fs.readFile(gcodesFilePath, (err: NodeJS.ErrnoException, data: Buffer) => {
    GCodeImporter.importText(String(data), onGCodeLoaded);
  });
});
