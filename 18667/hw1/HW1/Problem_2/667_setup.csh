

if (`uname` == "Linux") then 

   echo "## Seting up the 18-667 Linux Environment ##"

   # Synplify Path.
   setenv PATH /afs/ece.cmu.edu/support/synplicity/7.1/i386_suse73/image/usr/local/synplicity/bin:${PATH}

else if (`uname` == "SunOS") then

   echo "## Seting up the 18-667 Sun Environment ##"

   # Synplify Path.
   setenv PATH /afs/ece.cmu.edu/support/synplicity/7.1/sun4x_58/image/usr/local/synplicity/bin:${PATH}

endif


# Setup the VSIM/ModelSim Path.
setenv MGC_HOME /afs/ece/support/mgc/share/image/usr/local/mgc/C.2
setenv PATH /afs/ece/support/mgc/share/image/usr/local/mgc/modelsim/modeltech/bin:${PATH}

# Setup the License file for MG ModelSim
if ( ${?LM_LICENSE_FILE} ) then
   setenv LM_LICENSE_FILE ${LM_LICENSE_FILE}:${MGC_HOME}/license.dat
else
   setenv LM_LICENSE_FILE ${MGC_HOME}/license.dat
endif

# Setup the License file for synplify pro
if ( ${?LM_LICENSE_FILE} ) then
   setenv LM_LICENSE_FILE 7592@encore.ece.cmu.edu:${LM_LICENSE_FILE}
else
   setenv LM_LICENSE_FILE 7592@encore.ece.cmu.edu
endif
