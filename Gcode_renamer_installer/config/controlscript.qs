

function Controller()
{

}


Controller.prototype.IntroductionPageCallback = function()
{
    if (installer.isUninstaller()) {
        // Get the current wizard page
        var widget = gui.currentPageWidget(); 
        if (widget != null) {
            // Don't show buttons because we just want to uninstall the software
            widget.findChild("PackageManagerRadioButton").visible = false;
            widget.findChild("UpdaterRadioButton").visible = false;
            widget.findChild("UninstallerRadioButton").visible = false;
        }
    }
}

Controller.prototype.LicenseAgreementPageCallback = function()
{
    var widget = gui.currentPageWidget();
    if (widget != null) {
        widget.AcceptLicenseRadioButton.checked = true;
    }
}

Controller.prototype.FinishedPageCallback = function() {

if (installer.isUninstaller() && installer.status == QInstaller.Success)  
    {
		installer.performOperation("Delete","@HomeDir@/AppData/Roaming/krzmazur1");
    }  
}