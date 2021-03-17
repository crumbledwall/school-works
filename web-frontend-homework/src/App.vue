<template>
  <div id="app">
    <router-view/>
  </div>
</template>

<script>


export default {
  name: 'App',
  components: {
  }
}
</script>

<style>
#app{
  text-align: center;
  width: 100%;
  position: relative;
}
::-webkit-scrollbar {display:none}
.bookss{
  width: 400px;
  height: 250px;
  position: absolute;
  line-height: 250px;
  font-size: 19px;
  opacity: 0;
  filter: alpha(opacity=0);
  transition: opacity 0.35s, transform 0.35s;
  color: #4a3a3a;
  top: 0px;
  margin: 0 auto;
  left: 0px;
  right: 0;
};
</style>
