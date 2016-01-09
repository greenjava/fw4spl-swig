import os
# Hack to load module dependencies
binDir = os.path.join(os.getcwd(), 'bin')
os.environ["PATH"] += os.pathsep + binDir

import xml.etree.ElementTree as ET
from fw4spl import Runtime
from fw4spl import Data
from fw4spl import Bundle
from fw4spl import Service
from fw4spl import Callback

print(">>Instantiate Runtime")
rtm = Runtime()
rtm.addBundles("./Bundles")
rtm.activateBundles()

print(">>Start servicesReg")
servicesReg = Bundle("servicesReg", "0.1")
servicesReg.start()

print(">>Start guiQt")
guiQt = Bundle("guiQt", "0.1")
guiQt.start()

print(">>Instantiate ::fwData::Image")
img = Data("::fwData::Image")

print(">>Print loaded Services (only 10 first)")
allServices = Service.getServices()
print(allServices[:10])

print(">>Print IReader Services for Image")
ioImageServices = Service.getServices("::fwData::Image", "::io::IReader")
print(ioImageServices)

print(">>Instantiate ::ioVTK::SImageReader")
iovtkReader = Service(img, "::ioVTK::SImageReader")
root = ET.Element("service")
ET.SubElement(root, "file").text = "D:/patients/patient_1.vtk"
iovtkReader.configure(ET.tostring(root))
iovtkReader.start()
iovtkReader.update()
iovtkReader.stop()

print(">>Instantiate ::gui::frame::SDefaultFrame")
frameSrv = Service(img, "::gui::frame::SDefaultFrame")
config = """<service>
            <gui>
                <frame>
                    <name>PythonApp</name>
                    <icon>Bundles/Tuto01Basic_0-1/tuto.ico</icon>
                    <minSize width="800" height="600" />
                </frame>
            </gui>
        </service>"""
frameSrv.configure(config)


class App(Callback):
  def call(self):
    frameSrv.start()


pyApp = App()
rtm.run(pyApp)

