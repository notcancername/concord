#ifndef SLACK_COMMON_H
#define SLACK_COMMON_H


#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"

struct slack_adapter {
  struct user_agent_s *ua;
  struct slack *p_client;
};

/* ADAPTER PRIVATE FUNCTIONS */
void slack_adapter_init(struct slack_adapter *adapter, const char config_file[]);
void slack_adapter_cleanup(struct slack_adapter *adapter);

void slack_adapter_run(
  struct slack_adapter *adapter, 
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...);

struct slack_rtm {
  struct websockets_s *ws;
  char base_url[UA_MAX_URL_LEN];
  struct { /* CALLBACKS STRUCTURE */
    idle_cb *on_idle; //trigers in every event loop iteration
    idle_cb *on_hello; //triggers when connections first establishes
    idle_cb *on_message;
  } cbs;
  struct slack *p_client;
};

/* RTM PRIVATE FUNCTIONS */
void slack_rtm_init(struct slack_rtm *rtm, const char config_file[]);
void slack_rtm_cleanup(struct slack_rtm *rtm);

struct slack_socketmode {
  struct websockets_s *ws;
  char base_url[UA_MAX_URL_LEN];
  struct slack *p_client;
};

/* SOCKET MODE PRIVATE FUNCTIONS */
void slack_socketmode_init(struct slack_socketmode *sm, const char config_file[]);
void slack_socketmode_cleanup(struct slack_socketmode *sm);

struct slack {
  struct slack_adapter adapter;
  struct slack_rtm rtm;
  struct slack_socketmode sm;
};

#endif // SLACK_COMMON_H
