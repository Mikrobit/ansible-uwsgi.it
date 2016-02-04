#include "httpd.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_config.h"
#include "http_connection.h"
#include "apr_strings.h"

static int dumb_remoteaddr_modify_request(request_rec *r) {
        char *remote = (char *) apr_table_get(r->headers_in, "X-Forwarded-For");
        if (!remote) return OK;
        char *last_comma = strrchr(remote, ',');
        if (last_comma) {
                if (strlen(last_comma) < 9) {
                        return HTTP_INTERNAL_SERVER_ERROR;
                }
                r->connection->remote_ip = apr_pstrdup(r->connection->pool, last_comma+2);
        }
        else {
                r->connection->remote_ip = apr_pstrdup(r->connection->pool, remote);
        }
        return OK;
}

static void register_hooks(apr_pool_t *p) {
    ap_hook_post_read_request(dumb_remoteaddr_modify_request, NULL, NULL, APR_HOOK_FIRST);
}

module AP_MODULE_DECLARE_DATA dumb_remoteaddr_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks,
};
