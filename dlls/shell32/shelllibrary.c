/*
 * ShellLibrary (Windows 7 libraries)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>

#define COBJMACROS

#include "wine/debug.h"
#include "windef.h"
#include "winbase.h"
#include "shlobj.h"
#include "shobjidl.h"

#include "shell32_main.h"

WINE_DEFAULT_DEBUG_CHANNEL(shell);

/* Wine has no libraries, so nothing ever loads as one.  Applications create
 * the object to find out whether a shell item is a library and treat a failed
 * load as "not a library"; failing to create the object at all is what breaks
 * them (TX16Wx's file browser threw on it and gave up its editor window). */

struct shell_library
{
    IShellLibrary IShellLibrary_iface;
    LONG ref;
};

static inline struct shell_library *impl_from_IShellLibrary(IShellLibrary *iface)
{
    return CONTAINING_RECORD(iface, struct shell_library, IShellLibrary_iface);
}

static HRESULT WINAPI shell_library_QueryInterface(IShellLibrary *iface, REFIID riid, void **obj)
{
    TRACE("(%p)->(%s %p)\n", iface, debugstr_guid(riid), obj);

    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IShellLibrary))
    {
        *obj = iface;
        IShellLibrary_AddRef(iface);
        return S_OK;
    }

    WARN("Unsupported interface %s.\n", debugstr_guid(riid));
    *obj = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI shell_library_AddRef(IShellLibrary *iface)
{
    struct shell_library *library = impl_from_IShellLibrary(iface);
    ULONG ref = InterlockedIncrement(&library->ref);
    TRACE("(%p) ref %lu\n", iface, ref);
    return ref;
}

static ULONG WINAPI shell_library_Release(IShellLibrary *iface)
{
    struct shell_library *library = impl_from_IShellLibrary(iface);
    ULONG ref = InterlockedDecrement(&library->ref);
    TRACE("(%p) ref %lu\n", iface, ref);
    if (!ref) free(library);
    return ref;
}

static HRESULT WINAPI shell_library_LoadLibraryFromItem(IShellLibrary *iface, IShellItem *item, DWORD mode)
{
    FIXME("(%p)->(%p %#lx) libraries are not supported\n", iface, item, mode);
    return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
}

static HRESULT WINAPI shell_library_LoadLibraryFromKnownFolder(IShellLibrary *iface, REFKNOWNFOLDERID id, DWORD mode)
{
    FIXME("(%p)->(%s %#lx) libraries are not supported\n", iface, debugstr_guid(id), mode);
    return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
}

static HRESULT WINAPI shell_library_AddFolder(IShellLibrary *iface, IShellItem *location)
{
    FIXME("(%p)->(%p) stub\n", iface, location);
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_RemoveFolder(IShellLibrary *iface, IShellItem *location)
{
    FIXME("(%p)->(%p) stub\n", iface, location);
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_GetFolders(IShellLibrary *iface, LIBRARYFOLDERFILTER filter, REFIID riid, void **ppv)
{
    FIXME("(%p)->(%d %s %p) stub\n", iface, filter, debugstr_guid(riid), ppv);
    if (ppv) *ppv = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_ResolveFolder(IShellLibrary *iface, IShellItem *folder, DWORD timeout,
                                                  REFIID riid, void **ppv)
{
    FIXME("(%p)->(%p %lu %s %p) stub\n", iface, folder, timeout, debugstr_guid(riid), ppv);
    if (ppv) *ppv = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_GetDefaultSaveFolder(IShellLibrary *iface, DEFAULTSAVEFOLDERTYPE type,
                                                         REFIID riid, void **ppv)
{
    FIXME("(%p)->(%d %s %p) stub\n", iface, type, debugstr_guid(riid), ppv);
    if (ppv) *ppv = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_SetDefaultSaveFolder(IShellLibrary *iface, DEFAULTSAVEFOLDERTYPE type, IShellItem *item)
{
    FIXME("(%p)->(%d %p) stub\n", iface, type, item);
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_GetOptions(IShellLibrary *iface, LIBRARYOPTIONFLAGS *options)
{
    FIXME("(%p)->(%p) stub\n", iface, options);
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_SetOptions(IShellLibrary *iface, LIBRARYOPTIONFLAGS mask, LIBRARYOPTIONFLAGS options)
{
    FIXME("(%p)->(%#x %#x) stub\n", iface, mask, options);
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_GetFolderType(IShellLibrary *iface, FOLDERTYPEID *ftid)
{
    FIXME("(%p)->(%p) stub\n", iface, ftid);
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_SetFolderType(IShellLibrary *iface, REFFOLDERTYPEID ftid)
{
    FIXME("(%p)->(%s) stub\n", iface, debugstr_guid(ftid));
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_GetIcon(IShellLibrary *iface, LPWSTR *icon)
{
    FIXME("(%p)->(%p) stub\n", iface, icon);
    if (icon) *icon = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_SetIcon(IShellLibrary *iface, LPCWSTR icon)
{
    FIXME("(%p)->(%s) stub\n", iface, debugstr_w(icon));
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_Commit(IShellLibrary *iface)
{
    FIXME("(%p) stub\n", iface);
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_Save(IShellLibrary *iface, IShellItem *folder, LPCWSTR name,
                                         LIBRARYSAVEFLAGS flags, IShellItem **saved_to)
{
    FIXME("(%p)->(%p %s %#x %p) stub\n", iface, folder, debugstr_w(name), flags, saved_to);
    if (saved_to) *saved_to = NULL;
    return E_NOTIMPL;
}

static HRESULT WINAPI shell_library_SaveInKnownFolder(IShellLibrary *iface, REFKNOWNFOLDERID folder, LPCWSTR name,
                                                      LIBRARYSAVEFLAGS flags, IShellItem **saved_to)
{
    FIXME("(%p)->(%s %s %#x %p) stub\n", iface, debugstr_guid(folder), debugstr_w(name), flags, saved_to);
    if (saved_to) *saved_to = NULL;
    return E_NOTIMPL;
}

static const IShellLibraryVtbl shell_library_vtbl =
{
    shell_library_QueryInterface,
    shell_library_AddRef,
    shell_library_Release,
    shell_library_LoadLibraryFromItem,
    shell_library_LoadLibraryFromKnownFolder,
    shell_library_AddFolder,
    shell_library_RemoveFolder,
    shell_library_GetFolders,
    shell_library_ResolveFolder,
    shell_library_GetDefaultSaveFolder,
    shell_library_SetDefaultSaveFolder,
    shell_library_GetOptions,
    shell_library_SetOptions,
    shell_library_GetFolderType,
    shell_library_SetFolderType,
    shell_library_GetIcon,
    shell_library_SetIcon,
    shell_library_Commit,
    shell_library_Save,
    shell_library_SaveInKnownFolder,
};

HRESULT WINAPI ShellLibrary_Constructor(IUnknown *outer, REFIID riid, void **obj)
{
    struct shell_library *library;
    HRESULT hr;

    TRACE("(%p %s %p)\n", outer, debugstr_guid(riid), obj);

    *obj = NULL;
    if (outer) return CLASS_E_NOAGGREGATION;

    if (!(library = calloc(1, sizeof(*library)))) return E_OUTOFMEMORY;
    library->IShellLibrary_iface.lpVtbl = &shell_library_vtbl;
    library->ref = 1;

    hr = IShellLibrary_QueryInterface(&library->IShellLibrary_iface, riid, obj);
    IShellLibrary_Release(&library->IShellLibrary_iface);
    return hr;
}
