_pkgname=qdmenu
pkgname=$_pkgname-git
pkgver=v1.0.7.g6f4012c
pkgrel=1
pkgdesc="A QML dmenu replacement"
arch=('i686' 'x86_64')
url=https://github.com/bayi/qdmenu
license=('MIT')
depends=('qt5-base' 'qt5-declarative' 'qt5-svg')
makedepends=('git' 'make')
source=("$_pkgname::git+https://github.com/bayi/qdmenu.git")
md5sums=('SKIP')
provides=("$_pkgname")
conflicts=("$_pkgname")

pkgver() {
  cd "$srcdir/$_pkgname"
  git describe --tags | sed 's|-|.|g'
}

build() {
    cd "$srcdir/$_pkgname"
    qmake
    make
}

package() {
    cd "$srcdir/$_pkgname"
    install -Dm755 "$srcdir/$_pkgname/qdmenu" "$pkgdir/usr/bin/qdmenu"
    install -Dm755 "$srcdir/$_pkgname/qdmenu-terminal" "$pkgdir/usr/bin/qdmenu-terminal"
}
