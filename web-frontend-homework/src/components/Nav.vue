<template>
  <div class="nav">
    <nav>
      <router-link :to="'/'" class="path">index</router-link>
      <router-link :to="'/catagery'" class="path">catagery</router-link>
      <router-link :to="'/show'" class="path">show</router-link>
      <router-link :to="'/login'" class="path"
        ><font-awesome-icon icon="user-secret" /> login</router-link
      >
      <router-link :to="'/'" @click.native="logout">logout</router-link>
    </nav>
  </div>
</template>

<script>

export default {
  name: "Nav",
  methods: {
    logout: function () {
      this.$cookies.remove("login");
    }
  }
};
</script>

<style>
nav {
  position: absolute;
  margin: 0 auto;
}
nav a {
  padding: 10px 20px;
  font-size: 16px;
  height: 56px;
  line-height: 56px;
  color: #999;
}
.router-link-exact-active.path {
  border-bottom: 2px solid teal;
  color: #333;
}
.topic {
  position: absolute;
  left: 0;
}
.nav {
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  height: 70px;
  background-color: rgb(255, 255, 255);
  width: 50vw;
  margin: 0 auto;
  position: fixed;
  right: 0;
  top: 0;
  left: 0;
  z-index: 999;
}
.el-menu-item {
  line-height: 50px;
  height: 40px;
}
a {
  text-decoration: none;
}
</style>
