openecar_dashboard#

Application to decode an display some data from CAN-bus of Mercedes Smart fortwo electric 2014. Initially it has beed written for Abylay Ospan <aospan@jokersys.com>

HIER
can-proto    -- CAN-protocol decoder  
data-sample  -- some CAN samples and dumps 
desktop      -- application, uses can-proto. It's Qt project
doc          -- documentatuin (must be... )
pictures     -- originals of screen pictures

BUILDING
You must start QtCreator (I had used 4.0.2 with Qt 5.7.0) and point it to desctop/openecar_dashboard.pro, then you must configure prohect to your Kits and ask Creator to build project. It must do it! I hope...


