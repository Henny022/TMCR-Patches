#include <global.h>

typedef struct {
    struct {
        u32 data;
        u32 status;
    } tx, rx;
} scriptio_t;

//extern volatile scriptio_t gScriptIO;
#define gScriptIO (*(volatile scriptio_t*)0x02038560)

// nonblocking send
inline void scriptio_send(u32 data)
{
    while (gScriptIO.tx.status);
    gScriptIO.tx.data = data;
    gScriptIO.tx.status = TRUE;
}

// blocking receive
inline u32 scriptio_recv()
{
    while(!gScriptIO.rx.status);
    u32 t = gScriptIO.rx.data;
    gScriptIO.rx.status = FALSE;
    return t;
}
