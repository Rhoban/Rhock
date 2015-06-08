#ifndef _RHOCK_EVENT_H
#define _RHOCK_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "context.h"
#include "program.h"

#ifndef RHOCK_EVENT
#define RHOCK_EVENT
#endif

/**
 * This is called on the startup, and when all the program are being killed
 */
extern void rhock_on_all_stopped() RHOCK_EVENT;
extern void rhock_on_reset() RHOCK_EVENT;

/**
 * Called when a program is controlled
 */
extern void rhock_on_run(struct rhock_program *program) RHOCK_EVENT;
extern void rhock_on_freeze(struct rhock_program *program) RHOCK_EVENT;
extern void rhock_on_kill(struct rhock_program *program) RHOCK_EVENT;

/**
 * Called when a context is controlled
 */
extern void rhock_on_start(struct rhock_context *context) RHOCK_EVENT;
extern void rhock_on_pause(struct rhock_context *context) RHOCK_EVENT;
extern void rhock_on_stop(struct rhock_context *context) RHOCK_EVENT;

/**
 * Called when the monitor infos are sent
 */
extern void rhock_on_monitor() RHOCK_EVENT;

/**
 * Called when a packet is received. This should return 1 if the command was
 * processed. Else, an unknown command ack will be sent.
 */
extern char rhock_on_packet(uint8_t type) RHOCK_EVENT;

#ifdef __cplusplus
}
#endif

#endif
