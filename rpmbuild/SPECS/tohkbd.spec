# Binary-only-installer-RPM for tohkbd
#
#
%define        __spec_install_post %{nil}
%define          debug_package %{nil}
%define        __os_install_post %{_dbpath}/brp-compress

Summary: The Other Half QWERTY Keyboard
Name: tohkbd
Version: 0.28
Release: 1
License: MIT
Group: Development/Tools
SOURCE0 : %{name}-%{version}.tar.gz
URL: https://github.com/kimmoli/tohkbd

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root

%description
%{summary}

%prep
%setup -q

%build
# Empty section.

%install
rm -rf %{buildroot}
mkdir -p  %{buildroot}

# in builddir
cp -a * %{buildroot}


%clean
rm -rf %{buildroot}


%files
%defattr(-,root,root,-)
%{_sbindir}/*
/etc/systemd/system/%{name}.service
/usr/share/maliit/plugins/com/jolla/layouts/%{name}.*

%post
systemctl enable %{name}.service
systemctl start %{name}.service

%preun
systemctl stop %{name}.service
systemctl disable %{name}.service

%changelog
* Sun Mar 23 2014  Kimmo Lindholm <kimmo.lindholm@gmail.com> 0.28-1
- First RPM

