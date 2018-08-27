openecar_dashboard#

Application to decode and display some data from CAN-bus of Mercedes Smart fortwo electric 2014. Initially it has beed written for Abylay Ospan <aospan@jokersys.com> by andy@ahome.ru

HIER

can-proto    -- CAN-protocol decoder  

data-sample  -- some CAN samples and dumps 

desktop      -- application, uses can-proto. It's Qt project

doc          -- documentatuin (must be... )

pictures     -- originals of screen pictures

BUILDING

You must start QtCreator (I had used 4.0.2 with Qt 5.7.0) and point it to desktop/openecar_dashboard.pro, then you must configure prohect to your Kits and ask Creator to build project. It must do it! I hope...

RUN

Run-time options:

  -h, --help                Displays this help.
  
  -d, --device <interface>  interface to use for CAN-bus access
  

  -c, --can_dump            dump all CAN messages
  
  -f, --fullscreen          start in full-screen mode

duble click switches normal and fullscreen modes
