Ansible playbook for uwsgi.it
===

To create a LAMP stack on a uwsgi.it container launch:

```
ansible-playbook -i hosts lamp.yml -e "host='your_uwsgi.it_server' user='your_container_id' password='your_mysql_password' remotes='your_smtp_server' domain='your_domain'"
```

And for single service installation:

```
ansible-playbook -i hosts apache.yml -e "host='your_uwsgi.it_server' user='your_container_id' domain='your_domain'"
```
