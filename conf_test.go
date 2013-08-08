package alpm

import (
	"bytes"
	"io/ioutil"
	"os"
	"reflect"
	"testing"
)

const pacmanConf = `
#
# GENERAL OPTIONS
#
[options]
RootDir     = /
DBPath      = /var/lib/pacman
CacheDir    = /var/cache/pacman/pkg /other/cachedir
LogFile     = /var/log/pacman.log
GPGDir      = /etc/pacman.d/gnupg/
HoldPkg     = pacman glibc
#XferCommand = /usr/bin/curl -C - -f %u > %o
XferCommand = /usr/bin/wget --passive-ftp -c -O %o %u
CleanMethod = KeepInstalled
UseDelta    = 0.7
Architecture = auto

# Pacman won't upgrade packages listed in IgnorePkg and members of IgnoreGroup
IgnorePkg   = hello world
IgnoreGroup = kde

#NoUpgrade   =
#NoExtract   =

# Misc options
#UseSyslog
Color
#TotalDownload
CheckSpace
VerbosePkgLists

# By default, pacman accepts packages signed by keys that its local keyring
# trusts (see pacman-key and its man page), as well as unsigned packages.
SigLevel    = Required DatabaseOptional
LocalFileSigLevel = Optional
#RemoteFileSigLevel = Required

[core]
Server = ftp://ftp.example.com/foobar/$repo/os/$arch/

[custom]
Server = file:///home/custompkgs
`

var pacmanConfRef = PacmanConfig{
	RootDir:      "/",
	DBPath:       "/var/lib/pacman",
	CacheDir:     []string{"/var/cache/pacman/pkg", "/other/cachedir"},
	LogFile:      "/var/log/pacman.log",
	GPGDir:       "/etc/pacman.d/gnupg/",
	HoldPkg:      []string{"pacman", "glibc"},
	XferCommand:  "/usr/bin/wget --passive-ftp -c -O %o %u",
	Architecture: "auto",
	CleanMethod:  "KeepInstalled",
	UseDelta:     "0.7",
	IgnorePkg:    []string{"hello", "world"},
	IgnoreGroup:  []string{"kde"},
	NoUpgrade:    nil,
	NoExtract:    nil,

	Options: ConfColor | ConfCheckSpace | ConfVerbosePkgLists,

	Repos: []RepoConfig{
		{Name: "core", Servers: []string{"ftp://ftp.example.com/foobar/$repo/os/$arch/"}},
		{Name: "custom", Servers: []string{"file:///home/custompkgs"}},
	},
}

func detailedDeepEqual(t *testing.T, x, y interface{}) {
	v := reflect.ValueOf(x)
	w := reflect.ValueOf(y)
	if v.Type() != w.Type() {
		t.Errorf("differing types %T vs. %T", x, y)
		return
	}
	for i := 0; i < v.NumField(); i++ {
		v_fld := v.Field(i).Interface()
		w_fld := w.Field(i).Interface()
		if !reflect.DeepEqual(v_fld, w_fld) {
			t.Errorf("field %s differs: got %#v, expected %#v",
				v.Type().Field(i).Name, v_fld, w_fld)
		}
	}
}

func TestPacmanConfigParser(t *testing.T) {
	buf := bytes.NewBufferString(pacmanConf)
	conf, err := ParseConfig(buf)
	if err != nil {
		t.Error(err)
	}

	detailedDeepEqual(t, conf, pacmanConfRef)
}

func TestPacmanConfigParserFile(t *testing.T) {
	tf, err := ioutil.TempFile("/tmp", "alpm_test")
	if err != nil {
		t.Error(err)
	}
	name := tf.Name()
	_, err = tf.Write([]byte(pacmanConf))
	if err != nil {
		t.Error(err)
	}
	tf.Close()
	f, err := os.Open(name)
	if err != nil {
		t.Error(err)
	}
	conf, err := ParseConfig(f)
	if err != nil {
		t.Error(err)
	}
	detailedDeepEqual(t, conf, pacmanConfRef)
}
