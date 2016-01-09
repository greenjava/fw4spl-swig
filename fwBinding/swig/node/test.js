var path = require('path')
// Hack to load module dependencies
var binDir = path.join(process.cwd(), "bin")
process.env.PATH += path.delimiter + binDir;

var fw4spl = require("fw4spl");

console.log(">>Instantiate Runtime");
var rtm = new fw4spl.Runtime();
rtm.addBundles("./Bundles");
rtm.activateBundles();

console.log(">>Start servicesReg");
var servicesReg = new fw4spl.Bundle("servicesReg", "0.1");
servicesReg.start();

console.log(">>Instantiate ::fwData::Image");
var img = new fw4spl.Data("::fwData::Image");

console.log(">>Print loaded Services (only 10 first)");
var allServices = fw4spl.Service.getServices();
for(var i = 0; i < allServices.size() && i < 10; ++i){
    console.log(allServices.get(i));
}

console.log(">>Print IReader Services for Image");
var ioImageServices = fw4spl.Service.getServices("::fwData::Image", "::io::IReader");
for(var i = 0; i < ioImageServices.size(); ++i){
    console.log(ioImageServices.get(i));
}

console.log(">>Instantiate ::ioVTK::SImageReader");
var iovtkReader = new fw4spl.Service(img, "::ioVTK::SImageReader");
iovtkReader.configure("<service><file>D:/patients/patient_1.vtk</file></service>");
iovtkReader.start();
iovtkReader.update();
iovtkReader.stop();


process.exit();
