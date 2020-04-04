const electron = require('electron');
const path = require('path');
const fs = require('fs');

electron.ipcRenderer.on('show-gcodes', (event, gcodesFilePath) => {
    console.log("show", gcodesFilePath);
});