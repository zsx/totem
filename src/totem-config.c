#include <glib.h>
#include <gconf/gconf-client.h>
#include <windows.h>
#include <stdio.h>

static GConfClient defaultClient;

#ifdef _MSC_VER
#define __func__ __FUNCTION__
#endif

#define REG_PREFIX L"Software\\Gnome"

#ifdef _UNICODE
#define gcharp2LPCTSTR(p, out) \
	do{ \
		int bytes = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, p, strlen(p), out, 256); \
		out[bytes] = L'\0';\
	}while(0)
#define LPCTSTR2gcharp(p, out) \
	do{ \
		int bytes = WideCharToMultiByte(CP_UTF8, MB_ERR_INVALID_CHARS, p, -1, out, 0, NULL, NULL); \
		out = malloc(bytes); \
		bytes = WideCharToMultiByte(CP_UTF8, MB_ERR_INVALID_CHARS, p, -1, out, bytes, NULL, NULL); \
		out[bytes] = '\0';\
	}while(0)
#else
#define gcharp2LPCTSTR(p, out) \
	do{\
		out = p;\
	}while(0)

#define LPCTSTR2gcharp(p, out) gcharp2LPCTSTR(p, out)

#endif

/* 
 * @param value: a pointer to a pre-allocaed char buffer of size at least 256 bytes
 */
static gboolean open_key(const gchar *key, TCHAR *value, REGSAM samDesired, PHKEY h)
{
	char *name = NULL;
	char *key1 = NULL;
	int ret = 0;
	key1 = g_strdup(key);
	if(key1 == NULL)
		return FALSE;
	if(RegOpenKeyEx(HKEY_CURRENT_USER, REG_PREFIX, 0, samDesired, h) != ERROR_SUCCESS){
		g_print("open key failed\n");
		return FALSE;
	}
	name = strrchr(key1, '/');
	if(name != NULL){
		*name = '\0';
		name ++;
	}else{
		name = key;
		g_free(key1);
		key1 = NULL;
	}
	if(key1 != NULL){
		TCHAR k1[256];
		gcharp2LPCTSTR(key1, k1);
		ret = RegOpenKeyEx(*h, k1, 0, samDesired, h); 
		if(ret != ERROR_SUCCESS){
			TCHAR msg[512];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ret, 0, msg, sizeof(msg), NULL);
			g_print("open key(%s) failed2: %S\n", key1, msg);
			g_free(key1);
			return FALSE;
		}
		g_free(key1);
	}
	gcharp2LPCTSTR(name, value);
	g_print("name = %s\n", name);
	printf("value = %S\n", value);

	return TRUE;
}

GConfClient*        
gconf_client_get_default            (void)
{
	return &defaultClient;
};

GConfClient*        
gconf_client_get_for_engine         (GConfEngine *engine)
{
	return &defaultClient;
}

void                gconf_client_add_dir                (GConfClient *client,
                                                         const gchar *dir,
                                                         GConfClientPreloadType preload,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_remove_dir             (GConfClient *client,
                                                         const gchar *dir,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
}
guint               gconf_client_notify_add             (GConfClient *client,
                                                         const gchar *namespace_section,
                                                         GConfClientNotifyFunc func,
                                                         gpointer user_data,
                                                         GFreeFunc destroy_notify,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return 0;
}
void                gconf_client_notify_remove          (GConfClient *client,
                                                         guint cnxn)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_notify                 (GConfClient *client,
                                                         const char *key)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_set_error_handling     (GConfClient *client,
                                                         GConfClientErrorHandlingMode mode)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_set_global_default_error_handler
                                                        (GConfClientErrorHandlerFunc func)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_clear_cache            (GConfClient *client)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_preload                (GConfClient *client,
                                                         const gchar *dirname,
                                                         GConfClientPreloadType type,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_set                    (GConfClient *client,
                                                         const gchar *key,
                                                         const GConfValue *val,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
}
GConfValue*         gconf_client_get                    (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
GConfValue*         gconf_client_get_without_default    (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
GConfEntry*         gconf_client_get_entry              (GConfClient *client,
                                                         const gchar *key,
                                                         const gchar *locale,
                                                         gboolean use_schema_default,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
GConfValue*         gconf_client_get_default_from_schema
                                                        (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
gboolean            gconf_client_unset                  (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
gboolean            gconf_client_recursive_unset        (GConfClient *client,
                                                         const char *key,
                                                         GConfUnsetFlags flags,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
GSList*             gconf_client_all_entries            (GConfClient *client,
                                                         const gchar *dir,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
GSList*             gconf_client_all_dirs               (GConfClient *client,
                                                         const gchar *dir,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
void                gconf_client_suggest_sync           (GConfClient *client,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
}
gboolean            gconf_client_dir_exists             (GConfClient *client,
                                                         const gchar *dir,
                                                         GError **err)
{
	g_print("stub: %s, dir = %s\n", __func__, dir);
	return FALSE;
}
gboolean            gconf_client_key_is_writable        (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
gdouble             gconf_client_get_float              (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return 0.0;
}
gint                gconf_client_get_int                (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	HKEY h;
	DWORD data = 0;
	DWORD size = sizeof(data);
	static TCHAR value[256];
	int ret = 0;
	if(!open_key(key, value, KEY_QUERY_VALUE, &h))
		return FALSE;
	ret = RegQueryValueEx(h, value, NULL, NULL, (LPBYTE)&data, &size);
	if(ret != ERROR_SUCCESS){
		g_print("query failed with error %d\n", ret);
		return FALSE;
	}
	g_print("stub: %s, %s = %u\n", __func__, key, data);
	RegCloseKey(h);
	return (int)data;
}
gchar*              gconf_client_get_string             (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	HKEY h;
	TCHAR * data = NULL;
	DWORD size = 256 * sizeof(TCHAR);
	static TCHAR value[256];
	int ret = 0;
	gchar *out = NULL;
	if(!open_key(key, value, KEY_QUERY_VALUE, &h))
		return FALSE;

	data = malloc(size);
	do{
		ret = RegQueryValueEx(h, value, NULL, NULL, (LPBYTE)&data, &size);
		if(ret != ERROR_SUCCESS){
			if(ret == ERROR_MORE_DATA){
				size += 256*sizeof(TCHAR);
				data = realloc(data, size);
			}
			g_print("query failed with error %d\n", ret);
			return FALSE;
		}
		break;
	}while(1);
	LPCTSTR2gcharp(data, out);
	free(data);
	g_print("stub: %s, %s = %u\n", __func__, key, data);
	RegCloseKey(h);
	return out;
}
gboolean            gconf_client_get_bool               (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	return gconf_client_get_int(client, key, err);
}

GConfSchema*        gconf_client_get_schema             (GConfClient *client,
                                                         const gchar *key,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
GSList*             gconf_client_get_list               (GConfClient *client,
                                                         const gchar *key,
                                                         GConfValueType list_type,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
gboolean            gconf_client_get_pair               (GConfClient *client,
                                                         const gchar *key,
                                                         GConfValueType car_type,
                                                         GConfValueType cdr_type,
                                                         gpointer car_retloc,
                                                         gpointer cdr_retloc,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
gboolean            gconf_client_set_float              (GConfClient *client,
                                                         const gchar *key,
                                                         gdouble val,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
gboolean            gconf_client_set_int                (GConfClient *client,
                                                         const gchar *key,
                                                         gint val,
                                                         GError **err)
{
	HKEY h;
	static TCHAR value[256];
	int ret = 0;
	if(!open_key(key, value, KEY_SET_VALUE, &h))
		return FALSE;
	ret = RegSetValueEx(h, value, 0, REG_DWORD, (LPBYTE)&val, sizeof(val));
	if(ret != ERROR_SUCCESS){
		g_print("SetValueEx failed with error %d\n", ret);
		return FALSE;
	}
	RegCloseKey(h);
	return TRUE;
}
gboolean            gconf_client_set_string             (GConfClient *client,
                                                         const gchar *key,
                                                         const gchar *val,
                                                         GError **err)
{
	HKEY h;
	TCHAR value[256];
	int ret = 0;
	TCHAR *val1 = NULL;
	int bytes = 0;
	if(!open_key(key, value, KEY_SET_VALUE, &h))
		return FALSE;
#ifdef _UNICODE
	bytes = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, val, -1, val1, 0);
	val1 = malloc(bytes * sizeof(TCHAR));
	bytes = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, val, -1, val1, bytes);
	val1[bytes] = L'\0';
	ret = RegSetValueEx(h, value, 0, REG_SZ, (LPBYTE)&val1, bytes * sizeof(TCHAR));
	free(val1);
#else
	ret = RegSetValueEx(h, value, 0, REG_SZ, (LPBYTE)&val, strlen(val) + 1);
#endif
	if(ret != ERROR_SUCCESS){
		g_print("SetValueEx failed with error %d\n", ret);
		return FALSE;
	}
	RegCloseKey(h);
	return TRUE;
}
gboolean            gconf_client_set_bool               (GConfClient *client,
                                                         const gchar *key,
                                                         gboolean val,
                                                         GError **err)
{
	return gconf_client_set_int(client, key, val, err);
}

gboolean            gconf_client_set_schema             (GConfClient *client,
                                                         const gchar *key,
                                                         const GConfSchema *val,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
gboolean            gconf_client_set_list               (GConfClient *client,
                                                         const gchar *key,
                                                         GConfValueType list_type,
                                                         GSList *list,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
gboolean            gconf_client_set_pair               (GConfClient *client,
                                                         const gchar *key,
                                                         GConfValueType car_type,
                                                         GConfValueType cdr_type,
                                                         gconstpointer address_of_car,
                                                         gconstpointer address_of_cdr,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
void                gconf_client_error                  (GConfClient *client,
                                                         GError *error)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_unreturned_error       (GConfClient *client,
                                                         GError *error)
{
	g_print("stub: %s\n", __func__);
}
void                gconf_client_value_changed          (GConfClient *client,
                                                         const gchar *key,
                                                         GConfValue *value)
{
	g_print("stub: %s\n", __func__);
}
gboolean            gconf_client_commit_change_set      (GConfClient *client,
                                                         GConfChangeSet *cs,
                                                         gboolean remove_committed,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return FALSE;
}
GConfChangeSet*     gconf_client_reverse_change_set     (GConfClient *client,
                                                         GConfChangeSet *cs,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
GConfChangeSet*     gconf_client_change_set_from_currentv
                                                        (GConfClient *client,
                                                         const gchar **keys,
                                                         GError **err)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}
GConfChangeSet*     gconf_client_change_set_from_current
                                                        (GConfClient *client,
                                                         GError **err,
                                                         const gchar *first_key,
                                                         ...)
{
	g_print("stub: %s\n", __func__);
	return NULL;
}

