#include <stdio.h>

#include "nova.h"





int main(NOVA_MULTIPLE_ARGS)
{

    nova_App* QuattEditorApp = nova_StartApp(800, 600, "QuattEditorApp", 0);
    nova_App* QuattEditorToolApp = nova_StartApp(500, 550, "QuattEditorToolApp", 0);
    
    nova_NewApp(QuattEditorApp, QuattEditorToolApp);




    nova_Run(QuattEditorApp);
}